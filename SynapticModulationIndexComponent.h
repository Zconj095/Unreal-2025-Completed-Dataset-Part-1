#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticModulationIndexComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticModulationIndexComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticModulationIndexComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="SMI")
    float Beta = 1.0f;

    UPROPERTY(EditAnywhere, Category="SMI")
    float DeltaS = 2.5f;

    UPROPERTY(EditAnywhere, Category="SMI")
    float DeltaT = 1.0f;

    float CalculateSMI(float BetaValue, float DeltaSValue, float DeltaTValue) const;
};
