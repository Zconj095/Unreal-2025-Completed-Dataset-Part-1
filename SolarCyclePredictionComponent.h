#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarCyclePredictionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarCyclePredictionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarCyclePredictionComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float Amplitude = 100.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float Period = 11.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float PhaseOffset = 0.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float Time = 5.0f;

    float PredictAmplitude(float A0, float T, float Phi, float TimeValue) const;
};
