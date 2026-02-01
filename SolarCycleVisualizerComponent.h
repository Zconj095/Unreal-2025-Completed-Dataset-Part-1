#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarCycleVisualizerComponent.generated.h"

class UTextRenderComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarCycleVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarCycleVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float AmplitudeBase = 100.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float Period = 11.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float PhaseOffset = 0.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    float TimeValue = 5.0f;

    UPROPERTY(EditAnywhere, Category="Solar Cycle")
    UTextRenderComponent* DisplayText = nullptr;

    float PredictAmplitude(float A0, float T, float Phi, float Time) const;
};
