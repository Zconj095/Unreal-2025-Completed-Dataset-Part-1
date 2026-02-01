#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalHarmonicIntegrationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalHarmonicIntegrationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalHarmonicIntegrationComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    UPROPERTY(EditAnywhere, Category="Seasonal Harmonics")
    float H0 = 1.0f;

    UPROPERTY(EditAnywhere, Category="Seasonal Harmonics")
    float Gamma = 0.5f;

    UPROPERTY(EditAnywhere, Category="Seasonal Harmonics")
    float OmegaJ = 2.0f * PI / 365.0f;

    UPROPERTY(EditAnywhere, Category="Seasonal Harmonics")
    float Phi = 0.0f;

    UPROPERTY(EditAnywhere, Category="Seasonal Harmonics")
    float SimulationDuration = 10.0f;

    UPROPERTY(EditAnywhere, Category="Seasonal Harmonics")
    int32 Resolution = 100;

private:
    float StartTime = 0.0f;
    void SimulateHarmonicIntegration() const;
};
