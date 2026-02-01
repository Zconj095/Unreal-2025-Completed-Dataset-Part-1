#include "CelestialNeuralResonanceComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"
#include <complex>

UCelestialNeuralResonanceComponent::UCelestialNeuralResonanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCelestialNeuralResonanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (EnergyAmplitudes.Num() != SourcesCount)
	{
		EnergyAmplitudes.Init(1.0f, SourcesCount);
	}
	if (Frequencies.Num() != SourcesCount)
	{
		Frequencies.Init(0.5f, SourcesCount);
	}
	if (PhaseShifts.Num() != SourcesCount)
	{
		PhaseShifts.Init(0.0f, SourcesCount);
	}
}

void UCelestialNeuralResonanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	std::complex<float> Sum(0.0f, 0.0f);
	for (int32 Index = 0; Index < SourcesCount; ++Index)
	{
		const float Angle = 2.0f * PI * Frequencies[Index] * TimeSeconds + PhaseShifts[Index];
		const float CosAngle = FMath::Cos(Angle);
		const float SinAngle = FMath::Sin(Angle);
		const std::complex<float> Harmonic = EnergyAmplitudes[Index] * std::complex<float>(CosAngle, SinAngle);
		Sum += Harmonic;
	}
	ResonanceValue = Sum.real();
	UE_LOG(LogTemp, Log, TEXT("ψ_celestial(t): %0.4f"), ResonanceValue);
}
