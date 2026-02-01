#include "AtomicNeuralResonanceComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAtomicNeuralResonanceComponent::UAtomicNeuralResonanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAtomicNeuralResonanceComponent::BeginPlay()
{
	Super::BeginPlay();
	SimulationTime = 0.0f;
	NeuralActivity = CalculateNeuralActivity(SimulationTime);
}

void UAtomicNeuralResonanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SimulationTime += DeltaTime;
	NeuralActivity = CalculateNeuralActivity(SimulationTime);
	if (bLogActivity)
	{
		UE_LOG(LogTemp, Log, TEXT("Neural Activity at %0.2f s: %0.4f"), SimulationTime, NeuralActivity);
	}
}

float UAtomicNeuralResonanceComponent::CalculateNeuralActivity(float TimeSeconds) const
{
	const float Angular = 2.0f * PI * Frequency * TimeSeconds;
	return BaselineActivity * (1.0f + ResonanceAmplitude * FMath::Sin(Angular));
}

void UAtomicNeuralResonanceComponent::ResetResonance()
{
	SimulationTime = 0.0f;
	NeuralActivity = CalculateNeuralActivity(SimulationTime);
}
