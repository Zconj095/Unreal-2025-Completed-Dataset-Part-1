#include "ArchitectonicCortexComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UArchitectonicCortexComponent::UArchitectonicCortexComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UArchitectonicCortexComponent::BeginPlay()
{
	Super::BeginPlay();

	SimulateTraining();

	TArray<float> Inputs;
	Inputs.Init(0.0f, InputSize);
	for (int32 Index = 0; Index < InputSize; ++Index)
	{
		Inputs[Index] = (Index + 1) * 0.1f;
	}

	GenerateBlueprint(Inputs);
}

void UArchitectonicCortexComponent::GenerateBlueprint(const TArray<float>& Inputs)
{
	const int32 Dimension = FMath::Max(BlueprintDimension, 1);
	const int32 TotalSamples = Dimension * Dimension * Dimension;

	ResetBlueprint();

	BlueprintData.SetNum(TotalSamples);

	bool bHasCustomInputs = Inputs.Num() == InputSize && InputSize > 0;
	const TArray<float>* InputPtr = bHasCustomInputs ? &Inputs : nullptr;

	for (int32 Index = 0; Index < TotalSamples; ++Index)
	{
		const float Value = SampleBlueprintValue(InputPtr, Index);
		BlueprintData[Index] = Value;
	}

	if (bLogBlueprint)
	{
		LogBlueprint();
	}
}

void UArchitectonicCortexComponent::ResetBlueprint()
{
	BlueprintData.Reset();
}

void UArchitectonicCortexComponent::LogBlueprint() const
{
	if (BlueprintData.Num() == 0)
	{
		return;
	}

	const int32 Dimension = FMath::Max(BlueprintDimension, 1);
	UE_LOG(LogTemp, Log, TEXT("Architectonic Blueprint (%dx%dx%d):"), Dimension, Dimension, Dimension);

	for (int32 Z = 0; Z < Dimension; ++Z)
	{
		FString LayerLine = TEXT("Layer ");
		LayerLine.AppendInt(Z);
		LayerLine.Append(TEXT(": "));

		for (int32 Index = Z * Dimension * Dimension; Index < (Z + 1) * Dimension * Dimension; ++Index)
		{
			const float Value = BlueprintData.IsValidIndex(Index) ? BlueprintData[Index] : 0.0f;
			LayerLine += FString::Printf(TEXT("%0.3f "), Value);
		}

		UE_LOG(LogTemp, Log, TEXT("%s"), *LayerLine);
	}
}

void UArchitectonicCortexComponent::SimulateTraining() const
{
	FString LayerString;
	for (int32 HiddenLayerSize : HiddenLayers)
	{
		if (LayerString.Len() > 0)
		{
			LayerString += TEXT(", ");
		}
		LayerString += FString::FromInt(HiddenLayerSize);
	}

	UE_LOG(LogTemp, Log, TEXT("Simulated architectonic training using layers [%s]."), *LayerString);
}

float UArchitectonicCortexComponent::SampleBlueprintValue(const TArray<float>* Inputs, int32 Index) const
{
	const float PositionModifier = Index / float(FMath::Max(OutputSize, 1));

	float InputContribution = 0.0f;
	if (Inputs && Inputs->Num() > 0)
	{
		for (float Value : *Inputs)
		{
			InputContribution += Value;
		}
	}
	else
	{
		InputContribution = InputSize * 0.05f;
	}

	float HiddenContribution = 0.0f;
	for (int32 LayerSize : HiddenLayers)
	{
		HiddenContribution += LayerSize * 0.001f;
	}

	const float Base = InputContribution * 0.1f + HiddenContribution * 0.2f + PositionModifier;
	return 0.5f + 0.5f * FMath::Sin(Base + Index * 0.01f);
}
