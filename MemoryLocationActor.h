// Demo actor for MemoryLocationManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryLocationManager.h"
#include "MemoryLocationActor.generated.h"

UCLASS()
class PEKBGGAP_API AMemoryLocationActor : public AActor
{
    GENERATED_BODY()

public:
    AMemoryLocationActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMemoryLocationManager* Manager;
};

