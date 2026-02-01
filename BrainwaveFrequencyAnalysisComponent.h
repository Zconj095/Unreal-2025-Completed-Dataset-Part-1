#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainwaveFrequencyAnalysisComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBrainwaveFrequencyAnalysisComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBrainwaveFrequencyAnalysisComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Power amplitude factor (A). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brainwave")
	float PowerAmplitude = 1.0f;

	/** Damping constant (B). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brainwave")
	float DampingConstant = 0.1f;

	/** Modulation constant (C). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brainwave")
	float ModulationConstant = 2.0f;

	/** Frequency (f). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brainwave")
	float Frequency = 10.0f;

	/** Spectral power density result. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Brainwave")
	float SpectralPowerDensity = 0.0f;

	/** Computes ?(f) = A·e^(−Bf)·cos(Cf). */
	UFUNCTION(BlueprintCallable, Category = "Brainwave")
	float CalculateSpectralPowerDensity(float Amplitude, float Damping, float Modulation, float Freq) const;
};
