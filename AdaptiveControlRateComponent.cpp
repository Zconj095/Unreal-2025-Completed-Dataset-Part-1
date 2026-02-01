#include "AdaptiveControlRateComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAdaptiveControlRateComponent::UAdaptiveControlRateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveControlRateComponent::BeginPlay()
{
	Super::BeginPlay();

	AdaptiveControlRate = CalculateAdaptiveControlRate();
	UE_LOG(LogTemp, Log, TEXT("Adaptive Control Rate (Ra): %0.4f"), AdaptiveControlRate);
	RunTensorFlowPlaceholder();
}

float UAdaptiveControlRateComponent::CalculateAdaptiveControlRate() const
{
	const float Exponential = FMath::Exp(-DecayConstant * TimeSeconds);
	return InitialAdaptationRate * Exponential + MagicalEnergyContribution;
}

void UAdaptiveControlRateComponent::RunTensorFlowPlaceholder() const
{
	// Mirror the Unity TensorFlow validation with logs for transparency.
	const float Result = CalculateAdaptiveControlRate();
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: R0=%0.2f, λ=%0.2f, t=%0.2f, μΦ=%0.2f -> Ra=%0.4f"),
		InitialAdaptationRate, DecayConstant, TimeSeconds, MagicalEnergyContribution, Result);
}
