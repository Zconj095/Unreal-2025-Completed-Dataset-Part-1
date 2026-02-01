// Demo actor for MemoryRetentionRateManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryRetentionRateManager.h"
#include "MemoryRetentionRateActor.generated.h"

UCLASS()
class PEKBGGAP_API AMemoryRetentionRateActor : public AActor
{
    GENERATED_BODY()

public:
    AMemoryRetentionRateActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMemoryRetentionRateManager* Manager;
};

