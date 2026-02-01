#include "AtomicDisintegrationControlComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAtomicDisintegrationControlComponent::UAtomicDisintegrationControlComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtomicDisintegrationControlComponent::BeginPlay()
{
	Super::BeginPlay();

	DisintegrationControl = CalculateDisintegrationControl(NeuralPrecision, InputEnergy, ThresholdEnergy);
	if (ThresholdEnergy <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("AtomicDisintegrationControlComponent: ThresholdEnergy must be > 0."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Atomic Disintegration Control (Da): %0.4f"), DisintegrationControl);
	}
}

float UAtomicDisintegrationControlComponent::CalculateDisintegrationControl(float NeuralPrecisionValue, float InputEnergyValue, float ThresholdEnergyValue) const
{
	if (ThresholdEnergyValue <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	return NeuralPrecisionValue * (InputEnergyValue / ThresholdEnergyValue);
}
