#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarHarmonicModulationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarHarmonicModulationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarHarmonicModulationComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Harmony")
    float H0 = 1.0f;

    UPROPERTY(EditAnywhere, Category="Harmony")
    float Gamma = 0.5f;

    UPROPERTY(EditAnywhere, Category="Harmony")
    float OmegaS = 2.0f;

    UPROPERTY(EditAnywhere, Category="Harmony")
    float Phi = 0.0f;

    float TimeElapsed = 0.0f;

    float CalculateNeuralHarmony(float Time) const;
};
