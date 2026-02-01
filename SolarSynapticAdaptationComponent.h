#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarSynapticAdaptationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarSynapticAdaptationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarSynapticAdaptationComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Synaptic Adaptation")
    float BaselineConnectivity = 1.0f;

    UPROPERTY(EditAnywhere, Category="Synaptic Adaptation")
    float Sensitivity = 0.5f;

    UPROPERTY(EditAnywhere, Category="Synaptic Adaptation")
    float SolarIntensity = 100.0f;

    UPROPERTY(EditAnywhere, Category="Synaptic Adaptation")
    float SolarFrequency = 0.1f;

    float TimeElapsed = 0.0f;

    float CalculateSynapticAdaptability(float Time) const;
};
