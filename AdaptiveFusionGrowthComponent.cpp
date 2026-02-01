#include "AdaptiveFusionGrowthComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAdaptiveFusionGrowthComponent::UAdaptiveFusionGrowthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveFusionGrowthComponent::BeginPlay()
{
	Super::BeginPlay();

	const float FusionGrowthRate = CalculateFusionGrowthRate();
	UE_LOG(LogTemp, Log, TEXT("Fusion Growth Rate G_f(t): %0.4f"), FusionGrowthRate);
	RunTensorFlowPlaceholder();
}

float UAdaptiveFusionGrowthComponent::CalculateFusionGrowthRate() const
{
	const float EnergySum = EnergyContribution1 + EnergyContribution2;
	return InitialGrowthRate * FMath::Exp(GrowthConstant * EnergySum);
}

void UAdaptiveFusionGrowthComponent::RunTensorFlowPlaceholder() const
{
	const float Result = CalculateFusionGrowthRate();
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: G0=%0.2f, k=%0.2f, E1=%0.2f, E2=%0.2f -> G_f(t)=%0.4f"),
		InitialGrowthRate, GrowthConstant, EnergyContribution1, EnergyContribution2, Result);
}
