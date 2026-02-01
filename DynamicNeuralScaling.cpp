#include "DynamicNeuralScaling.h"
#include "Engine/Engine.h"

ADynamicNeuralScaling::ADynamicNeuralScaling()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADynamicNeuralScaling::BeginPlay()
{
	Super::BeginPlay();

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxCapacity must be positive for DynamicNeuralScaling."));
		return;
	}

	NeuralCapacity = CalculateNeuralCapacity();
	UE_LOG(LogTemp, Log, TEXT("Dynamic Neural Scaling for Psychology (N_p(%.2f)): %.2f"), TimeSeconds, NeuralCapacity);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Dynamic Neural Scaling N_p(%.2f): %.2f"), TimeSeconds, NeuralCapacity));
	}
}

float ADynamicNeuralScaling::CalculateNeuralCapacity() const
{
	const float Factor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialNeuralCapacity * FMath::Pow(Factor, TimeSeconds);
}
