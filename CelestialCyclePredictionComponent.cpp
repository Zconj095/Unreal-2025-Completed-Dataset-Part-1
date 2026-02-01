#include "CelestialCyclePredictionComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

static constexpr double GravitationalConstant = 6.67430e-11;

UCelestialCyclePredictionComponent::UCelestialCyclePredictionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCelestialCyclePredictionComponent::BeginPlay()
{
	Super::BeginPlay();

	OrbitalPeriodSeconds = CalculateOrbitalPeriod(SemiMajorAxis, CentralMass);
	OrbitalPeriodYears = OrbitalPeriodSeconds / (60.0f * 60.0f * 24.0f * 365.25f);

	UE_LOG(LogTemp, Log, TEXT("Orbital Period: %0.4f seconds (%0.2f years)"), OrbitalPeriodSeconds, OrbitalPeriodYears);
}

float UCelestialCyclePredictionComponent::CalculateOrbitalPeriod(float SemiMajorAxisValue, float CentralMassValue) const
{
	if (SemiMajorAxisValue <= KINDA_SMALL_NUMBER || CentralMassValue <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("Semi-major axis and central mass must be greater than zero."));
		return 0.0f;
	}

	return static_cast<float>((2.0 * PI * FMath::Pow(SemiMajorAxisValue, 1.5f)) / FMath::Sqrt(GravitationalConstant * CentralMassValue));
}
