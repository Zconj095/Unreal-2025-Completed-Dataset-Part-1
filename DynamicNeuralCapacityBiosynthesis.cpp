#include "DynamicNeuralCapacityBiosynthesis.h"

ADynamicNeuralCapacityBiosynthesis::ADynamicNeuralCapacityBiosynthesis()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADynamicNeuralCapacityBiosynthesis::BeginPlay()
{
	Super::BeginPlay();

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxCapacity must be positive for DynamicNeuralCapacityBiosynthesis."));
		return;
	}

	NeuralCapacity = CalculateNeuralCapacity(Time);
	UE_LOG(LogTemp, Log, TEXT("Dynamic Neural Capacity for Biosynthesis (N_b(t)): %.2f"), NeuralCapacity);
}

float ADynamicNeuralCapacityBiosynthesis::CalculateNeuralCapacity(float TimeSeconds) const
{
	const float GrowthFactor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialCapacity * FMath::Pow(GrowthFactor, TimeSeconds);
}
