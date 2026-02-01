#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalEnergyModelComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalEnergyModelComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalEnergyModelComponent();

    static double CalculateSeasonalEnergy(double Amplitude, double Period, double PhaseShift, double Time);

protected:
    virtual void BeginPlay() override;
};
