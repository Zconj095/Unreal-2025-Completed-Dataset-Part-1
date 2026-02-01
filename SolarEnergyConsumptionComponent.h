#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarEnergyConsumptionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarEnergyConsumptionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarEnergyConsumptionComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Energy Consumption")
    float BaselineEnergy = 50.0f;

    UPROPERTY(EditAnywhere, Category="Energy Consumption")
    float SolarEnergy = 20.0f;

    UPROPERTY(EditAnywhere, Category="Energy Consumption")
    float OmegaS = 2.0f;

    UPROPERTY(EditAnywhere, Category="Energy Consumption")
    float ObservationPeriod = 10.0f;

    UPROPERTY(EditAnywhere, Category="Energy Consumption")
    int32 Steps = 100;

    float CalculateEnergyConsumption() const;
    float EnergyFunction(float Time) const;
};
