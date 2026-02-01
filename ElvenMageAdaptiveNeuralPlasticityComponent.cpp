#include "ElvenMageAdaptiveNeuralPlasticityComponent.h"
#include "Logging/LogMacros.h"

UElvenMageAdaptiveNeuralPlasticityComponent::UElvenMageAdaptiveNeuralPlasticityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UElvenMageAdaptiveNeuralPlasticityComponent::BeginPlay()
{
	Super::BeginPlay();

	PlasticityRate = CalculatePlasticityRate(Alpha, DeltaS, Beta, Phi);
	UE_LOG(LogTemp, Log, TEXT("Plasticity Rate (P): %0.4f"), PlasticityRate);

	LogNeuralNetworkPrediction();
	LogTensorFlowComputation();
}

float UElvenMageAdaptiveNeuralPlasticityComponent::CalculatePlasticityRate(float InAlpha, float InDeltaS, float InBeta, float InPhi) const
{
	return InAlpha * InDeltaS + InBeta * InPhi;
}

void UElvenMageAdaptiveNeuralPlasticityComponent::LogNeuralNetworkPrediction() const
{
	const float Predicted = CalculatePlasticityRate(Alpha, DeltaS, Beta, Phi);
	UE_LOG(LogTemp, Log, TEXT("Mock NN Prediction: α=%0.2f ΔS=%0.2f β=%0.2f Φ=%0.2f -> P=%0.4f"),
		Alpha, DeltaS, Beta, Phi, Predicted);
}

void UElvenMageAdaptiveNeuralPlasticityComponent::LogTensorFlowComputation() const
{
	const float Computed = CalculatePlasticityRate(Alpha, DeltaS, Beta, Phi);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: P = α·ΔS + β·Φ => %0.4f"), Computed);
}
