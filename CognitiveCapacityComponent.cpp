#include "CognitiveCapacityComponent.h"

UCognitiveCapacityComponent::UCognitiveCapacityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveCapacityComponent::BeginPlay()
{
	Super::BeginPlay();

	CognitiveCapacity = CalculateCognitiveCapacity();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Capacity: %.4f"), CognitiveCapacity);
}

float UCognitiveCapacityComponent::CalculateCognitiveCapacity() const
{
	return Proportionality * EventDensity * Adaptability;
}
