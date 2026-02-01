#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalSynapticPlasticityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalSynapticPlasticityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalSynapticPlasticityComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void SimulateSynapticPlasticity() const;

    UPROPERTY(EditAnywhere, Category="Synaptic Plasticity")
    float S0 = 1.0f;

    UPROPERTY(EditAnywhere, Category="Synaptic Plasticity")
    float Beta = 0.5f;

    UPROPERTY(EditAnywhere, Category="Synaptic Plasticity")
    float Tb = 0.8f;

    UPROPERTY(EditAnywhere, Category="Synaptic Plasticity")
    float OmegaJ = 2.0f * PI / 365.0f;

    UPROPERTY(EditAnywhere, Category="Simulation")
    float SimulationDuration = 10.0f;

    UPROPERTY(EditAnywhere, Category="Simulation")
    int32 Resolution = 100;
};
