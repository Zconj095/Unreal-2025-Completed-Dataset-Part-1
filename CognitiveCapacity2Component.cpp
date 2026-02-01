#include "CognitiveCapacity2Component.h"

UCognitiveCapacity2Component::UCognitiveCapacity2Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveCapacity2Component::BeginPlay()
{
	Super::BeginPlay();
	CognitiveCapacity = CalculateCapacity();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Capacity (Ca): %.4f"), CognitiveCapacity);
}

float UCognitiveCapacity2Component::CalculateCapacity() const
{
	return Scaling * AtomicDensity * NeuralEfficiency;
}
