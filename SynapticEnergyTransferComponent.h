#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticEnergyTransferComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticEnergyTransferComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticEnergyTransferComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Synaptic Energy")
    double BrainTemperature = 310.0;

    UPROPERTY(EditAnywhere, Category="Synaptic Energy", meta=(ClampMin="0.0", ClampMax="1.0"))
    double QuantumCoherenceEfficiency = 0.8;

    double CalculateSynapticEnergy(double Temperature, double QuantumEfficiency) const;
};
