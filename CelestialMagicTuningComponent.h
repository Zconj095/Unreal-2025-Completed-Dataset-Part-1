#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialMagicTuningComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialMagicTuningComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialMagicTuningComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Number of stellar sources. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Magic")
	int32 StellarSourceCount = 5;

	/** Amplitudes (A_n). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Magic")
	TArray<float> Amplitudes;

	/** Frequencies (f_n). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Magic")
	TArray<float> Frequencies;

	/** Phase alignments (φ_n). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Magic")
	TArray<float> PhaseAlignments;

	/** Cached magnitude. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Magic")
	float Magnitude = 0.0f;

	/** Cached real part. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Magic")
	float RealPart = 0.0f;

	/** Cached imaginary part. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Magic")
	float ImaginaryPart = 0.0f;
};
