#include "BioinformaticsNeuralNetworkComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBioinformaticsNeuralNetworkComponent::UBioinformaticsNeuralNetworkComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBioinformaticsNeuralNetworkComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Weights.Num() != NumberOfInputs || Inputs.Num() != NumberOfInputs)
	{
		UE_LOG(LogTemp, Error, TEXT("Weights and inputs arrays must match NumberOfInputs."));
		return;
	}

	NeuronOutput = CalculateNeuronOutput();
	UE_LOG(LogTemp, Log, TEXT("Neuron Output (O_i): %0.4f"), NeuronOutput);
}

float UBioinformaticsNeuralNetworkComponent::CalculateNeuronOutput() const
{
	float WeightedSum = Bias;
	for (int32 Index = 0; Index < NumberOfInputs; ++Index)
	{
		WeightedSum += Weights[Index] * Inputs[Index];
	}
	return ApplyActivation(WeightedSum);
}

float UBioinformaticsNeuralNetworkComponent::ApplyActivation(float Value) const
{
	switch (ActivationFunction)
	{
	case EBioinformaticsActivationFunction::Sigmoid:
		return 1.0f / (1.0f + FMath::Exp(-Value));
	case EBioinformaticsActivationFunction::ReLU:
		return FMath::Max(0.0f, Value);
	default:
		UE_LOG(LogTemp, Error, TEXT("Invalid activation type."));
		return 0.0f;
	}
}
