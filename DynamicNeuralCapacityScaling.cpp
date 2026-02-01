#include "DynamicNeuralCapacityScaling.h"

ADynamicNeuralCapacityScaling::ADynamicNeuralCapacityScaling()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralCapacityScaling::BeginPlay()
{
	Super::BeginPlay();
	NeuralCapacity = InitialCapacity;
	TimeSeconds = 0.0f;
}

void ADynamicNeuralCapacityScaling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralCapacityScaling requires MaxCapacity > 0."));
		return;
	}

	TimeSeconds += DeltaTime;
	NeuralCapacity = CalculateNeuralCapacity(TimeSeconds);
	UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Neural Capacity: %.2f"), TimeSeconds, NeuralCapacity);
}

float ADynamicNeuralCapacityScaling::CalculateNeuralCapacity(float InTimeSeconds) const
{
	const float GrowthFactor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialCapacity * FMath::Pow(GrowthFactor, InTimeSeconds);
}

void ADynamicNeuralCapacityScaling::SetInitialCapacity(float Value)
{
	InitialCapacity = Value;
}

void ADynamicNeuralCapacityScaling::SetGrowthRate(float Value)
{
	GrowthRate = Value;
}

void ADynamicNeuralCapacityScaling::SetMaxCapacity(float Value)
{
	MaxCapacity = Value;
}

void ADynamicNeuralCapacityScaling::ResetTime()
{
	TimeSeconds = 0.0f;
}
