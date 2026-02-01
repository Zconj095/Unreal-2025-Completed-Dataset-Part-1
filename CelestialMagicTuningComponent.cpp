#include "CelestialMagicTuningComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"
#include <complex>

UCelestialMagicTuningComponent::UCelestialMagicTuningComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCelestialMagicTuningComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCelestialMagicTuningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const int32 Count = FMath::Max(StellarSourceCount, 1);
	if (Amplitudes.Num() != Count || Frequencies.Num() != Count || PhaseAlignments.Num() != Count)
	{
		UE_LOG(LogTemp, Warning, TEXT("Array lengths must equal StellarSourcesCount (%d)."), Count);
		return;
	}

	const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	std::complex<float> TotalEnergy(0.0f, 0.0f);

	for (int32 Index = 0; Index < Count; ++Index)
	{
		const float Angle = 2.0f * PI * Frequencies[Index] * TimeSeconds + PhaseAlignments[Index];
		const float CosAngle = FMath::Cos(Angle);
		const float SinAngle = FMath::Sin(Angle);
		const std::complex<float> Harmonic = Amplitudes[Index] * std::complex<float>(CosAngle, SinAngle);
		TotalEnergy += Harmonic;
	}

	Magnitude = std::abs(TotalEnergy);
	RealPart = TotalEnergy.real();
	ImaginaryPart = TotalEnergy.imag();
	UE_LOG(LogTemp, Log, TEXT("E_celestial magnitude: %0.4f real: %0.4f imaginary: %0.4f"), Magnitude, RealPart, ImaginaryPart);
}
