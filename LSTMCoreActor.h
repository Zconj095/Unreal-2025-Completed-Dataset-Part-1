// Demo actor for ULSTMMemoryManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSTMCoreManager.h"
#include "LSTMCoreActor.generated.h"

UCLASS()
class PEKBGGAP_API ALSTMCoreActor : public AActor
{
    GENERATED_BODY()

public:
    ALSTMCoreActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ULSTMMemoryManager* Manager;
};

