#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimulationAndTestingComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USimulationAndTestingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USimulationAndTestingComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Stress Test")
    double AppliedForce = 500.0;

    UPROPERTY(EditAnywhere, Category="Stress Test")
    double ElasticModulus = 250.0;

    double CalculateStressFactor(double Force, double Modulus) const;
};
