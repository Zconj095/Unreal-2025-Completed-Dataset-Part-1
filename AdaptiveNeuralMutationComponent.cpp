#include "AdaptiveNeuralMutationComponent.h"
#include "Logging/LogMacros.h"

UAdaptiveNeuralMutationComponent::UAdaptiveNeuralMutationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveNeuralMutationComponent::BeginPlay()
{
	Super::BeginPlay();

	RateOfNeuralMutations = CalculateNeuralMutationRate(MutationConstant, CurrentNeuralCapacity, MaximumCapacity);
	if (RateOfNeuralMutations > 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Rate of Neural Mutations (?N): %0.4f"), RateOfNeuralMutations);
	}
}

float UAdaptiveNeuralMutationComponent::CalculateNeuralMutationRate(float Mu, float N, float K) const
{
	if (K <= 0.0f || N < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("AdaptiveNeuralMutationComponent: Invalid parameters K=%0.2f N=%0.2f"), K, N);
		return 0.0f;
	}

	const float CapacityRatio = N / K;
	return Mu * N * (1.0f - CapacityRatio);
}
