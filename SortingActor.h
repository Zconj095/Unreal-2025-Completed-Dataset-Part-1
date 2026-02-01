// Demo actor for SortingManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortingManager.h"
#include "SortingActor.generated.h"

UCLASS()
class PEKBGGAP_API ASortingActor : public AActor
{
    GENERATED_BODY()

public:
    ASortingActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USortingManager* Manager;
};

