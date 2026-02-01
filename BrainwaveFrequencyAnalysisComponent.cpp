#include "BrainwaveFrequencyAnalysisComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBrainwaveFrequencyAnalysisComponent::UBrainwaveFrequencyAnalysisComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBrainwaveFrequencyAnalysisComponent::BeginPlay()
{
	Super::BeginPlay();

	SpectralPowerDensity = CalculateSpectralPowerDensity(PowerAmplitude, DampingConstant, ModulationConstant, Frequency);
	UE_LOG(LogTemp, Log, TEXT("Spectral Power Density (?f): %0.4f"), SpectralPowerDensity);
}

float UBrainwaveFrequencyAnalysisComponent::CalculateSpectralPowerDensity(float Amplitude, float Damping, float Modulation, float Freq) const
{
	return Amplitude * FMath::Exp(-Damping * Freq) * FMath::Cos(Modulation * Freq);
}
