#include "DynamicNeuralCapacity4.h"

ADynamicNeuralCapacity4::ADynamicNeuralCapacity4()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralCapacity4::BeginPlay()
{
	Super::BeginPlay();

	TimeElapsed = 0.0f;
	NeuralCapacity = InitialCapacity;
}

void ADynamicNeuralCapacity4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralCapacity4 requires MaxCapacity > 0."));
		return;
	}

	TimeElapsed += DeltaTime;
	NeuralCapacity = CalculateDNCB(TimeElapsed);
	UE_LOG(LogTemp, Log, TEXT("Time: %.2fs, Neural Capacity (Nb): %.2f"), TimeElapsed, NeuralCapacity);
}

float ADynamicNeuralCapacity4::CalculateDNCB(float TimeSeconds) const
{
	const float GrowthFactor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialCapacity * FMath::Pow(GrowthFactor, TimeSeconds);
}
