#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarEnergyResonanceComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarEnergyResonanceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarEnergyResonanceComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Resonance")
    float Amplitude = 1.0f;

    UPROPERTY(EditAnywhere, Category="Resonance")
    float CyclePeriod = 365.25f * 24.0f * 3600.0f;

    UPROPERTY(VisibleAnywhere, Category="Resonance")
    float CurrentTime = 0.0f;

    UPROPERTY(VisibleAnywhere, Category="Resonance")
    float ResonanceFactor = 0.0f;

    float CalculateSER(float A, float P, float Time) const;
};
