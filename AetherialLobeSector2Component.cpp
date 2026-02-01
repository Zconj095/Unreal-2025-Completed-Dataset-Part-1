#include "AetherialLobeSector2Component.h"
#include "Math/UnrealMathUtility.h"
#include "Logging/LogMacros.h"

UAetherialLobeSector2Component::UAetherialLobeSector2Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAetherialLobeSector2Component::BeginPlay()
{
	Super::BeginPlay();

	RebuildAetherialState();
}

void UAetherialLobeSector2Component::RebuildAetherialState()
{
	if (NumThreads <= 0 || StateSize <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AetherialLobeSector2Component: NumThreads and StateSize must be positive."));
		return;
	}

	GenerateRandomAmplitudes();
	GenerateRandomBasisThreads();
	NormalizeAmplitudes();
	ComputeBrainState();
	LogBrainState();
}

void UAetherialLobeSector2Component::GenerateRandomAmplitudes()
{
	Amplitudes.SetNum(NumThreads);
	for (int32 Index = 0; Index < NumThreads; ++Index)
	{
		Amplitudes[Index] = FMath::FRand();
	}
}

void UAetherialLobeSector2Component::GenerateRandomBasisThreads()
{
	BasisThreads.SetNum(StateSize * NumThreads);
	for (float& Value : BasisThreads)
	{
		Value = FMath::FRand();
	}
}

void UAetherialLobeSector2Component::NormalizeAmplitudes()
{
	float SumOfSquares = 0.0f;
	for (float Value : Amplitudes)
	{
		SumOfSquares += Value * Value;
	}

	const float Denominator = FMath::Sqrt(FMath::Max(SumOfSquares, KINDA_SMALL_NUMBER));
	for (float& Value : Amplitudes)
	{
		Value /= Denominator;
	}
}

void UAetherialLobeSector2Component::ComputeBrainState()
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
			const int32 MatrixIndex = ThreadIndex * StateSize + Row;
			BrainState[Row] += Amp * BasisThreads[MatrixIndex];
		}
	}
}

void UAetherialLobeSector2Component::LogBrainState() const
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

	UE_LOG(LogTemp, Log, TEXT("Total Brain State |Ψ⟩: [%s]"), *StateString);
}
