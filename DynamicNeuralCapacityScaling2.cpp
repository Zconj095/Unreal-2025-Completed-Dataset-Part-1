#include "DynamicNeuralCapacityScaling2.h"

ADynamicNeuralCapacityScaling2::ADynamicNeuralCapacityScaling2()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralCapacityScaling2::BeginPlay()
{
	Super::BeginPlay();
	TimeSeconds = 0.0f;
	NeuralCapacity = InitialCapacity;
}

void ADynamicNeuralCapacityScaling2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralCapacityScaling2 requires MaxCapacity > 0."));
		return;
	}

	TimeSeconds += DeltaTime;
	NeuralCapacity = CalculateNeuralCapacity(TimeSeconds);
	UE_LOG(LogTemp, Log, TEXT("Neural Capacity at time %.2f: %.2f"), TimeSeconds, NeuralCapacity);
}

float ADynamicNeuralCapacityScaling2::CalculateNeuralCapacity(float InTimeSeconds) const
{
	const float GrowthFactor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialCapacity * FMath::Pow(GrowthFactor, InTimeSeconds);
}

void ADynamicNeuralCapacityScaling2::SetInitialCapacity(float Value)
{
	InitialCapacity = Value;
}

void ADynamicNeuralCapacityScaling2::SetGrowthRate(float Value)
{
	GrowthRate = Value;
}

void ADynamicNeuralCapacityScaling2::SetMaxCapacity(float Value)
{
	MaxCapacity = Value;
}

void ADynamicNeuralCapacityScaling2::ResetTime()
{
	TimeSeconds = 0.0f;
}
