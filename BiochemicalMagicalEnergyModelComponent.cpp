#include "BiochemicalMagicalEnergyModelComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalMagicalEnergyModelComponent::UBiochemicalMagicalEnergyModelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiochemicalMagicalEnergyModelComponent::BeginPlay()
{
	Super::BeginPlay();

	BuildField();

	const int32 Size = FMath::Max(GridSize, 1);
	float TotalEnergy = 0.0f;

	for (int32 X = 1; X < Size - 1; ++X)
	{
		for (int32 Y = 1; Y < Size - 1; ++Y)
		{
			for (int32 Z = 1; Z < Size - 1; ++Z)
			{
				const float Value = SampleField(X, Y, Z);
				const float Gradient = ComputeGradientMagnitude(X, Y, Z);
				TotalEnergy += Value * Gradient * FMath::Square(DeltaSpacing) * DeltaSpacing;
			}
		}
	}

	TotalBiochemicalEnergy = TotalEnergy;
	if (bLogEnergy)
	{
		UE_LOG(LogTemp, Log, TEXT("Total Biochemical Energy: %0.4f"), TotalBiochemicalEnergy);
	}
}

void UBiochemicalMagicalEnergyModelComponent::BuildField()
{
	const int32 Size = FMath::Max(GridSize, 1);
	const int32 TotalCells = Size * Size * Size;
	MagicalField.SetNumZeroed(TotalCells);

	FRandomStream Rand(FDateTime::Now().GetTicks());
	for (int32 Index = 0; Index < TotalCells; ++Index)
	{
		const int32 X = Index % Size;
		const int32 Y = (Index / Size) % Size;
		const int32 Z = Index / (Size * Size);

		const float Phase = X * DeltaSpacing * 0.1f + Y * DeltaSpacing * 0.2f + Z * DeltaSpacing * 0.15f;
		float Value = FMath::Sin(Phase) * FMath::Cos(Y * DeltaSpacing) * FMath::Exp(-Z * DeltaSpacing) + Rand.FRandRange(0.0f, 0.1f);
		MagicalField[Index] = FMath::Clamp(Value, 0.0f, 1.0f);
	}
}

int32 UBiochemicalMagicalEnergyModelComponent::GetFlatIndex(int32 X, int32 Y, int32 Z) const
{
	const int32 Size = FMath::Max(GridSize, 1);
	return X + Y * Size + Z * Size * Size;
}

float UBiochemicalMagicalEnergyModelComponent::SampleField(int32 X, int32 Y, int32 Z) const
{
	const int32 Size = FMath::Max(GridSize, 1);
	if (X < 0 || X >= Size || Y < 0 || Y >= Size || Z < 0 || Z >= Size)
	{
		return 0.0f;
	}

	const int32 Index = GetFlatIndex(X, Y, Z);
	return MagicalField.IsValidIndex(Index) ? MagicalField[Index] : 0.0f;
}

float UBiochemicalMagicalEnergyModelComponent::ComputeGradientMagnitude(int32 X, int32 Y, int32 Z) const
{
	const float Dx = SampleField(X + 1, Y, Z) - SampleField(X - 1, Y, Z);
	const float Dy = SampleField(X, Y + 1, Z) - SampleField(X, Y - 1, Z);
	const float Dz = SampleField(X, Y, Z + 1) - SampleField(X, Y, Z - 1);
	const float Scale = 0.5f / FMath::Max(DeltaSpacing, KINDA_SMALL_NUMBER);
	return FMath::Sqrt(Dx * Dx + Dy * Dy + Dz * Dz) * Scale;
}
