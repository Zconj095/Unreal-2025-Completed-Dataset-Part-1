#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticEnergyIntegrationComponent.generated.h"

class UCurveFloat;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticEnergyIntegrationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticEnergyIntegrationComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Synaptic Energy")
    float FreeEnergyChange = 1.0f;

    UPROPERTY(EditAnywhere, Category="Synaptic Energy")
    UCurveFloat* EnergyFluxCurve = nullptr;

    float SynapticEnergy = 0.0f;
    float PreviousTime = 0.0f;
};
