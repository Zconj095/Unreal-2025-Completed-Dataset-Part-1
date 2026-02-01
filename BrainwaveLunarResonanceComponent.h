#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainwaveLunarResonanceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBrainwaveLunarResonanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBrainwaveLunarResonanceComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lunar Resonance")
	float Amplitude = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lunar Resonance")
	float LunarPhasePeriod = 29.53f * 24 * 3600;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lunar Resonance")
	float ResonanceFactor = 0.0f;

	/** Computes R_l = A * sin(2π t / P). */
	UFUNCTION(BlueprintCallable, Category = "Lunar Resonance")
	float CalculateBLR(float AmplitudeValue, float PhasePeriod, float TimeSeconds) const;
};
