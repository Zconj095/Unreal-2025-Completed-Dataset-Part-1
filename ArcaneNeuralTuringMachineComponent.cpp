#include "ArcaneNeuralTuringMachineComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UArcaneNeuralTuringMachineComponent::UArcaneNeuralTuringMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UArcaneNeuralTuringMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeMachine();
	SimulateTraining();
	PerformDemoSteps();
}

void UArcaneNeuralTuringMachineComponent::InitializeMachine()
{
	Tape.Init(0.0f, FMath::Max(TapeSize, 1));
	CurrentState.Init(0.0f, FMath::Max(StateSize, 1));
	HeadPosition = 0;
}

void UArcaneNeuralTuringMachineComponent::PerformDemoSteps()
{
	for (EArcaneTuringAction Action : DemoActions)
	{
		Step(Action);
	}
}

void UArcaneNeuralTuringMachineComponent::Step(EArcaneTuringAction Action)
{
	if (!Tape.IsValidIndex(HeadPosition))
	{
		HeadPosition = FMath::Clamp(HeadPosition, 0, Tape.Num() - 1);
		if (!Tape.IsValidIndex(HeadPosition))
		{
			return;
		}
	}

	const float CurrentSymbol = Tape[HeadPosition];
	const TArray<float> NextState = TransitionFunction(CurrentSymbol);

	switch (Action)
	{
	case EArcaneTuringAction::Write:
		Tape[HeadPosition] = ComputeStateNorm(NextState);
		break;
	case EArcaneTuringAction::MoveLeft:
		if (HeadPosition > 0)
		{
			HeadPosition--;
		}
		break;
	case EArcaneTuringAction::MoveRight:
		if (HeadPosition < Tape.Num() - 1)
		{
			HeadPosition++;
		}
		break;
	default:
		break;
	}

	CurrentState = NextState;
	LogMachineState();
}

TArray<float> UArcaneNeuralTuringMachineComponent::TransitionFunction(float Symbol) const
{
	TArray<float> NextState;
	NextState.Init(0.0f, CurrentState.Num());

	for (int32 Index = 0; Index < NextState.Num(); ++Index)
	{
		const float Base = CurrentState.IsValidIndex(Index) ? CurrentState[Index] : 0.0f;
		const float Modifier = 1.0f + Index * 0.15f;
		NextState[Index] = Base + Symbol * Modifier;
	}

	return NextState;
}

void UArcaneNeuralTuringMachineComponent::LogMachineState() const
{
	FString StateString;
	for (int32 Index = 0; Index < CurrentState.Num(); ++Index)
	{
		StateString += FString::Printf(TEXT("%0.4f"), CurrentState[Index]);
		if (Index < CurrentState.Num() - 1)
		{
			StateString += TEXT(", ");
		}
	}

	FString TapeString;
	for (int32 Index = 0; Index < Tape.Num(); ++Index)
	{
		TapeString += FString::Printf(TEXT("%0.2f"), Tape[Index]);
		if (Index < Tape.Num() - 1)
		{
			TapeString += TEXT(", ");
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Current State: [%s]"), *StateString);
	UE_LOG(LogTemp, Log, TEXT("Tape: [%s]"), *TapeString);
	UE_LOG(LogTemp, Log, TEXT("Head Position: %d"), HeadPosition);
}

void UArcaneNeuralTuringMachineComponent::SimulateTraining() const
{
	const int32 InputCount = FMath::Max(StateSize, 1);
	UE_LOG(LogTemp, Log, TEXT("Simulated training placeholder for the transition network using %d inputs."), InputCount);
}

float UArcaneNeuralTuringMachineComponent::ComputeStateNorm(const TArray<float>& State) const
{
	float SumSquares = 0.0f;
	for (float Value : State)
	{
		SumSquares += Value * Value;
	}

	return FMath::Sqrt(FMath::Max(SumSquares, KINDA_SMALL_NUMBER));
}
