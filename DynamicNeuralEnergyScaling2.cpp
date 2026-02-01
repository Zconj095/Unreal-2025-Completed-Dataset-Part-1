#include "DynamicNeuralEnergyScaling2.h"
#include "Engine/Engine.h"

ADynamicNeuralEnergyScaling2::ADynamicNeuralEnergyScaling2()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADynamicNeuralEnergyScaling2::BeginPlay()
{
	Super::BeginPlay();

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxCapacity must be greater than zero."));
		return;
	}

	NeuralCapacity = CalculateNeuralCapacity();
	UE_LOG(LogTemp, Log, TEXT("Neural Quantum Capacity N_q(%.2f) = %.2f"), TimeSeconds, NeuralCapacity);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Neural Quantum Capacity N_q(%.2f) = %.2f"), TimeSeconds, NeuralCapacity));
	}
}

float ADynamicNeuralEnergyScaling2::CalculateNeuralCapacity() const
{
	const float GrowthFactor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialCapacity * FMath::Pow(GrowthFactor, TimeSeconds);
}
