#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarEnergyAnalysisComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarEnergyAnalysisComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarEnergyAnalysisComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Solar Analysis")
    double TotalPowerOutput = 3.846e26;

    UPROPERTY(EditAnywhere, Category="Solar Analysis")
    double DistanceFromSun = 1.496e11;
};
