#include "BiochemicalEnergyVisualizerComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalEnergyVisualizerComponent::UBiochemicalEnergyVisualizerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiochemicalEnergyVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();

	BuildMagicalField();
	TotalBiochemicalEnergy = ComputeTotalBiochemicalEnergy();
	UE_LOG(LogTemp, Log, TEXT("Total Biochemical Energy: %0.4f"), TotalBiochemicalEnergy);

	if (bDrawDebugNodes)
	{
		DrawFieldDebug();
	}
}

void UBiochemicalEnergyVisualizerComponent::BuildMagicalField()
{
	const int32 Size = FMath::Max(GridSize, 1);
	const int32 TotalCells = Size * Size * Size;
	MagicalField.SetNum(TotalCells);

	for (int32 Index = 0; Index < TotalCells; ++Index)
	{
		const int32 X = Index % Size;
		const int32 Y = (Index / Size) % Size;
		const int32 Z = Index / (Size * Size);

		const float Phase = (float)X * DeltaSpacing * 0.1f + (float)Y * DeltaSpacing * 0.2f + (float)Z * DeltaSpacing * 0.15f;
		float Value = 0.5f + 0.5f * FMath::Sin(Phase);
		Value += 0.25f * FMath::Cos((float)Y * DeltaSpacing * 0.3f);

		MagicalField[Index] = FMath::Clamp(Value, 0.0f, 1.0f);
	}
}

float UBiochemicalEnergyVisualizerComponent::ComputeTotalBiochemicalEnergy()
{
	const int32 Size = FMath::Max(GridSize, 1);
	float Total = 0.0f;

	for (int32 X = 0; X < Size; ++X)
	{
		for (int32 Y = 0; Y < Size; ++Y)
		{
			for (int32 Z = 0; Z < Size; ++Z)
			{
				const float Value = SampleField(X, Y, Z);
				const float Gradient = ComputeGradientMagnitude(X, Y, Z);
				Total += FMath::Abs(Value * Gradient);
			}
		}
	}

	return Total;
}

int32 UBiochemicalEnergyVisualizerComponent::GetFlatIndex(int32 X, int32 Y, int32 Z) const
{
	const int32 Size = FMath::Max(GridSize, 1);
	return X + Y * Size + Z * Size * Size;
}

float UBiochemicalEnergyVisualizerComponent::SampleField(int32 X, int32 Y, int32 Z) const
{
	const int32 Size = FMath::Max(GridSize, 1);
	if (X < 0 || X >= Size || Y < 0 || Y >= Size || Z < 0 || Z >= Size)
	{
		return 0.0f;
	}

	const int32 Index = GetFlatIndex(X, Y, Z);
	return MagicalField.IsValidIndex(Index) ? MagicalField[Index] : 0.0f;
}

float UBiochemicalEnergyVisualizerComponent::ComputeGradientMagnitude(int32 X, int32 Y, int32 Z) const
{
	const float Dx = SampleField(X + 1, Y, Z) - SampleField(X - 1, Y, Z);
	const float Dy = SampleField(X, Y + 1, Z) - SampleField(X, Y - 1, Z);
	const float Dz = SampleField(X, Y, Z + 1) - SampleField(X, Y, Z - 1);
	const float Scale = 0.5f / FMath::Max(DeltaSpacing, KINDA_SMALL_NUMBER);
	return FMath::Sqrt((Dx * Dx + Dy * Dy + Dz * Dz)) * Scale;
}

void UBiochemicalEnergyVisualizerComponent::DrawFieldDebug() const
{
	if (!GetWorld())
	{
		return;
	}

	const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
	const int32 Size = FMath::Max(GridSize, 1);

	for (int32 X = 0; X < Size; ++X)
	{
		for (int32 Y = 0; Y < Size; ++Y)
		{
			for (int32 Z = 0; Z < Size; ++Z)
			{
				const float Value = SampleField(X, Y, Z);
				const float RenderSize = FMath::Max(0.1f, Value * ScaleMultiplier * DeltaSpacing);
				const FVector Location = Origin + FVector(X * DeltaSpacing, Y * DeltaSpacing, Z * DeltaSpacing);
				DrawDebugBox(GetWorld(), Location, FVector(RenderSize), NodeColor, false, DebugDuration, 0, 1.0f);
			}
		}
	}
}
