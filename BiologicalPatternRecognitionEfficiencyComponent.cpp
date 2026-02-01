#include "BiologicalPatternRecognitionEfficiencyComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiologicalPatternRecognitionEfficiencyComponent::UBiologicalPatternRecognitionEfficiencyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiologicalPatternRecognitionEfficiencyComponent::BeginPlay()
{
	Super::BeginPlay();

	PatternRecognitionEfficiency = CalculateBPRE(NeuralFiringRate, RecognitionTime, NeuralCost, Kappa);
	UE_LOG(LogTemp, Log, TEXT("Biological Pattern Recognition Efficiency (BPRE): %0.4f"), PatternRecognitionEfficiency);
}

float UBiologicalPatternRecognitionEfficiencyComponent::CalculateBPRE(float PhiValue, float TimeValue, float CostValue, float KappaValue) const
{
	if (TimeValue <= KINDA_SMALL_NUMBER || CostValue <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("Recognition Time and Neural Cost must be greater than 0."));
		return 0.0f;
	}

	return (KappaValue * PhiValue) / (TimeValue * CostValue);
}
