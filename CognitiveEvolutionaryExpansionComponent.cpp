#include "CognitiveEvolutionaryExpansionComponent.h"

#include "Math/UnrealMathUtility.h"

UCognitiveEvolutionaryExpansionComponent::UCognitiveEvolutionaryExpansionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveEvolutionaryExpansionComponent::BeginPlay()
{
	Super::BeginPlay();
	CEEValue = CalculateCEE();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Evolutionary Expansion (CEE): %.4f"), CEEValue);
}

float UCognitiveEvolutionaryExpansionComponent::CalculateCEE() const
{
	if (TotalNeurons <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Total Neurons (N) must be greater than zero."));
		return 0.0f;
	}

	const float LogTerm = FMath::Loge(1.0f + ConnectivityDensity) / FMath::Loge(2.0f);
	return Alpha * FMath::Pow(TotalNeurons, Dimensionality) * LogTerm;
}
