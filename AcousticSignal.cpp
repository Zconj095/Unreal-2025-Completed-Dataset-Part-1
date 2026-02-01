#include "AcousticSignal.h"
#include "Math/UnrealMathUtility.h"
#include "Logging/LogMacros.h"

float UAcousticSignal::CalculateIntensity(float InitialIntensity, float AttenuationCoefficient, float Distance)
{
	return InitialIntensity * FMath::Exp(-AttenuationCoefficient * Distance);
}

void UAcousticSignal::TestAcousticSignal()
{
	const float InitialIntensity = 100.0f;      // Initial sound intensity in arbitrary units
	const float AttenuationCoefficient = 0.1f;  // Attenuation per meter
	const float Distance = 50.0f;               // Distance in meters

	const float Intensity = CalculateIntensity(InitialIntensity, AttenuationCoefficient, Distance);

	UE_LOG(LogTemp, Log, TEXT("Sound Intensity at Distance %0.2f m: %0.4f"), Distance, Intensity);
}

