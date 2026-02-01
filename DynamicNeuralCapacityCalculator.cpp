#include "DynamicNeuralCapacityCalculator.h"

ADynamicNeuralCapacityCalculator::ADynamicNeuralCapacityCalculator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralCapacityCalculator::BeginPlay()
{
	Super::BeginPlay();

	CurrentTime = SimulationTime;
}

void ADynamicNeuralCapacityCalculator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeStep <= 0.0f || MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralCapacityCalculator requires positive TimeStep and MaxCapacity."));
		return;
	}

	CurrentTime += DeltaTime * TimeStep;
	const float NeuralCapacity = CalculateNeuralCapacity(CurrentTime);
	UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Neural Capacity (N_g): %.2f"), CurrentTime, NeuralCapacity);
}

float ADynamicNeuralCapacityCalculator::CalculateNeuralCapacity(float TimeSeconds) const
{
	const float GrowthBase = 1.0f + (GrowthRate / MaxCapacity);
	return InitialCapacity * FMath::Pow(GrowthBase, TimeSeconds);
}
