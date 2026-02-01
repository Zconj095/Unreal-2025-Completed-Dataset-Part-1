#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AcousticSignal.h"
#include "AcousticVisualizerActor.generated.h"

/**
 * Visualizes acoustic signal intensity over distance by spawning point actors.
 */
UCLASS()
class PEKBGGAP_API AAcousticVisualizerActor : public AActor
{
	GENERATED_BODY()

public:
	AAcousticVisualizerActor();

protected:
	virtual void BeginPlay() override;

private:
	/** Actor class used to visualize each intensity sample (similar to a prefab in Unity). */
	UPROPERTY(EditAnywhere, Category = "Acoustics")
	TSubclassOf<AActor> IntensityPointClass;

	/** Initial sound intensity in arbitrary units. */
	UPROPERTY(EditAnywhere, Category = "Acoustics")
	float InitialIntensity = 100.0f;

	/** Attenuation per meter. */
	UPROPERTY(EditAnywhere, Category = "Acoustics")
	float AttenuationCoefficient = 0.1f;

	/** Maximum distance to sample, in meters. */
	UPROPERTY(EditAnywhere, Category = "Acoustics")
	float MaxDistance = 100.0f;

	/** Distance step between samples, in meters. */
	UPROPERTY(EditAnywhere, Category = "Acoustics")
	float Step = 5.0f;
};

