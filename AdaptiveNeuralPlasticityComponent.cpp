#include "AdaptiveNeuralPlasticityComponent.h"
#include "Logging/LogMacros.h"

UAdaptiveNeuralPlasticityComponent::UAdaptiveNeuralPlasticityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveNeuralPlasticityComponent::BeginPlay()
{
	Super::BeginPlay();

	NeuralPlasticity = CalculateNeuralPlasticity(PlasticityCoefficient, EnvironmentalStimuli, GeneticStimuli);
	UE_LOG(LogTemp, Log, TEXT("Neural Plasticity (P): %0.4f"), NeuralPlasticity);
}

float UAdaptiveNeuralPlasticityComponent::CalculateNeuralPlasticity(float Kappa, float E, float G) const
{
	return Kappa * (E + G);
}
