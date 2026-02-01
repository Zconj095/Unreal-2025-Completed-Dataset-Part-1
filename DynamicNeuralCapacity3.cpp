#include "DynamicNeuralCapacity3.h"
#include "Engine/World.h"

ADynamicNeuralCapacity3::ADynamicNeuralCapacity3()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralCapacity3::BeginPlay()
{
	Super::BeginPlay();
}

void ADynamicNeuralCapacity3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaxNeuralCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralCapacity3 requires a positive MaxNeuralCapacity."));
		return;
	}

	const float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	const float NeuralCapacity = CalculateNeuralCapacity(CurrentTime);
	UE_LOG(LogTemp, Log, TEXT("Neural Capacity (Nn): %.2f"), NeuralCapacity);
}

float ADynamicNeuralCapacity3::CalculateNeuralCapacity(float TimeSeconds) const
{
	const float GrowthFactor = 1.0f + (GrowthRate / MaxNeuralCapacity);
	return InitialNeuralCapacity * FMath::Pow(GrowthFactor, TimeSeconds);
}
