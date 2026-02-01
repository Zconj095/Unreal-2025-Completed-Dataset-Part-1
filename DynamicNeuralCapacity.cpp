#include "DynamicNeuralCapacity.h"

ADynamicNeuralCapacity::ADynamicNeuralCapacity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralCapacity::BeginPlay()
{
	Super::BeginPlay();
	CurrentTime = 0.0f;
	NeuralCapacity = InitialCapacity;
}

void ADynamicNeuralCapacity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeStepFactor <= 0.0f || MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralCapacity requires positive TimeStepFactor and MaxCapacity."));
		return;
	}

	CurrentTime += DeltaTime * TimeStepFactor;
	NeuralCapacity = CalculateNeuralCapacity(CurrentTime);
	UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Neural Capacity (Ng): %.2f"), CurrentTime, NeuralCapacity);
}

float ADynamicNeuralCapacity::CalculateNeuralCapacity(float TimeSeconds) const
{
	const float GrowthBase = 1.0f + GrowthRate / MaxCapacity;
	return InitialCapacity * FMath::Pow(GrowthBase, TimeSeconds);
}
