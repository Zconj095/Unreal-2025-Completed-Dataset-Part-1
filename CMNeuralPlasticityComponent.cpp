#include "CMNeuralPlasticityComponent.h"

UCMNeuralPlasticityComponent::UCMNeuralPlasticityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCMNeuralPlasticityComponent::BeginPlay()
{
	Super::BeginPlay();
	NeuralPlasticity = PlasticityCoefficient * (CelestialStimuli + LuminosityStimuli);
}

void UCMNeuralPlasticityComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	NeuralPlasticity = PlasticityCoefficient * (CelestialStimuli + LuminosityStimuli);
	UE_LOG(LogTemp, Log, TEXT("Neural Plasticity (P_a): %.4f"), NeuralPlasticity);
}

void UCMNeuralPlasticityComponent::UpdateStimuli(float NewCelestial, float NewLuminosity)
{
	CelestialStimuli = NewCelestial;
	LuminosityStimuli = NewLuminosity;
}
