#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AcousticSignal.generated.h"

/**
 * Acoustic signal utilities for calculating sound intensity with distance-based attenuation.
 */
UCLASS(BlueprintType, Blueprintable)
class PEKBGGAP_API UAcousticSignal : public UObject
{
	GENERATED_BODY()

public:
	/** Calculate acoustic signal intensity: I = I0 * exp(-attenuationCoefficient * distance) */
	UFUNCTION(BlueprintCallable, Category = "Acoustics")
	static float CalculateIntensity(float InitialIntensity, float AttenuationCoefficient, float Distance);

	/** Simple test that logs an example intensity calculation to the output log. */
	UFUNCTION(BlueprintCallable, Category = "Acoustics")
	static void TestAcousticSignal();
};

