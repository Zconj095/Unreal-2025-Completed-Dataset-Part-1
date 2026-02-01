#include "CelestialSynchronizationComponent.h"

UCelestialSynchronizationComponent::UCelestialSynchronizationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCelestialSynchronizationComponent::BeginPlay()
{
	Super::BeginPlay();
	NeuralActivity = CalculateNeuralActivity(AccumulatedTime);
}

void UCelestialSynchronizationComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccumulatedTime += DeltaTime;
	NeuralActivity = CalculateNeuralActivity(AccumulatedTime);
	UE_LOG(LogTemp, Log, TEXT("Neural Activity at time %.2f: %.4f"), AccumulatedTime, NeuralActivity);
}

float UCelestialSynchronizationComponent::CalculateNeuralActivity(float TimeSeconds) const
{
	return BaselineActivity * (1.0f + Amplitude * FMath::Sin(AngularFrequency * TimeSeconds + PhaseOffset));
}
