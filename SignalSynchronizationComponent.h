#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SignalSynchronizationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USignalSynchronizationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USignalSynchronizationComponent();

protected:
    virtual void BeginPlay() override;

private:
    float CalculateSynchronizationEfficiency(float DeltaB, float DeltaM, float MagicalEnergy, float DeltaT) const;

    UPROPERTY(EditAnywhere, Category="Signal")
    float DeltaB = 1.0f;

    UPROPERTY(EditAnywhere, Category="Signal")
    float DeltaM = 2.0f;

    UPROPERTY(EditAnywhere, Category="Signal")
    float MagicalEnergy = 0.5f;

    UPROPERTY(EditAnywhere, Category="Signal")
    float DeltaT = 0.1f;
};
