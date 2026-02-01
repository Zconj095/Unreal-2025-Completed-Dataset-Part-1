// Demo actor for TemporalLSTMManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TemporalLSTMManager.h"
#include "TemporalLSTMActor.generated.h"

UCLASS()
class PEKBGGAP_API ATemporalLSTMActor : public AActor
{
    GENERATED_BODY()

public:
    ATemporalLSTMActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UTemporalLSTMManager* Manager;
};

