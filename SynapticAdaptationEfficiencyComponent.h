#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticAdaptationEfficiencyComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticAdaptationEfficiencyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticAdaptationEfficiencyComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="SAE")
    float BoltzmannConstant = 1.38e-23f;

    UPROPERTY(EditAnywhere, Category="SAE")
    float BrainTemperature = 310.0f;

    UPROPERTY(EditAnywhere, Category="SAE")
    float AdaptationEfficiency = 0.8f;

    float CalculateEnergyPerSynapticOperation(float Kb, float T, float Nu) const;
};
