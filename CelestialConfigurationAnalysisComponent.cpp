#include "CelestialConfigurationAnalysisComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UCelestialConfigurationAnalysisComponent::UCelestialConfigurationAnalysisComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCelestialConfigurationAnalysisComponent::BeginPlay()
{
	Super::BeginPlay();

	Distance = CalculateCelestialPosition(SemiMajorAxis, Eccentricity, OrbitalAngle, AngularVelocity, TimeSeconds);
	UE_LOG(LogTemp, Log, TEXT("Distance r(theta, t): %0.4f"), Distance);
}

float UCelestialConfigurationAnalysisComponent::CalculateCelestialPosition(float SemiMajor, float EccentricityValue, float Angle, float Omega, float TimeValue) const
{
	const float Denominator = 1.0f + EccentricityValue * FMath::Cos(Angle - Omega * TimeValue);
	if (FMath::IsNearlyZero(Denominator))
	{
		UE_LOG(LogTemp, Warning, TEXT("Denominator in celestial position calculation cannot be zero."));
		return 0.0f;
	}
	return SemiMajor * (1.0f - EccentricityValue * EccentricityValue) / Denominator;
}
