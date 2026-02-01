#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StellarEnergyAbsorptionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStellarEnergyAbsorptionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStellarEnergyAbsorptionComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Absorption")
    float Efficiency = 0.8f;

    UPROPERTY(EditAnywhere, Category="Absorption")
    float ObservationInterval = 10.0f;

    float CurrentTime = 0.0f;
    float AbsorbedEnergy = 0.0f;

    float CalculateFlux(float Time) const;
    void LogFinalEnergy() const;
};
