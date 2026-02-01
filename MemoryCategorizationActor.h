// Demo actor for MemoryCategorizationManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryCategorizationManager.h"
#include "MemoryCategorizationActor.generated.h"

UCLASS()
class PEKBGGAP_API AMemoryCategorizationActor : public AActor
{
    GENERATED_BODY()

public:
    AMemoryCategorizationActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMemoryCategorizationManager* Manager;
};

