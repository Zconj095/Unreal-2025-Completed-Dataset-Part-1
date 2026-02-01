#include "AetherialLobeComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Logging/LogMacros.h"

UAetherialLobeComponent::UAetherialLobeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAetherialLobeComponent::BeginPlay()
{
	Super::BeginPlay();

	RebuildAetherialState();
}

void UAetherialLobeComponent::RebuildAetherialState()
{
	if (NumThreads <= 0 || StateSize <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AetherialLobeComponent: NumThreads and StateSize must be positive."));
		return;
	}

	GenerateRandomAmplitudes();
	GenerateRandomMagicStates();
	NormalizeAmplitudes();
	ComputeBrainState();
	LogBrainState();
}

void UAetherialLobeComponent::GenerateRandomAmplitudes()
{
	Amplitudes.SetNum(NumThreads);
	for (int32 Index = 0; Index < NumThreads; ++Index)
	{
		Amplitudes[Index] = FMath::FRand();
	}
}

void UAetherialLobeComponent::GenerateRandomMagicStates()
{
	MagicStates.SetNum(StateSize * NumThreads);
	for (float& Value : MagicStates)
	{
		Value = FMath::FRand();
	}
}

void UAetherialLobeComponent::NormalizeAmplitudes()
{
	float SumOfSquares = 0.0f;
	for (float Amp : Amplitudes)
	{
		SumOfSquares += Amp * Amp;
	}

	const float Denominator = FMath::Sqrt(FMath::Max(SumOfSquares, KINDA_SMALL_NUMBER));
	for (float& Amp : Amplitudes)
	{
		Amp /= Denominator;
	}
}

void UAetherialLobeComponent::ComputeBrainState()
{
	BrainState.SetNum(StateSize);
	for (float& Value : BrainState)
	{
		Value = 0.0f;
	}

	for (int32 ThreadIndex = 0; ThreadIndex < NumThreads; ++ThreadIndex)
	{
		const float Amp = Amplitudes[ThreadIndex];
		for (int32 Row = 0; Row < StateSize; ++Row)
		{
			const int32 MatrixIndex = Row + ThreadIndex * StateSize;
			BrainState[Row] += Amp * MagicStates[MatrixIndex];
		}
	}
}

void UAetherialLobeComponent::LogBrainState() const
{
	FString StateString;
	for (int32 Index = 0; Index < BrainState.Num(); ++Index)
	{
		StateString += FString::Printf(TEXT("%0.4f"), BrainState[Index]);
		if (Index < BrainState.Num() - 1)
		{
			StateString += TEXT(", ");
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Aetherial Brain State |Ψ⟩: [%s]"), *StateString);
}
