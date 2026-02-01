// Demo actor for FilteringManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FilteringManager.h"
#include "FilteringActor.generated.h"

UCLASS()
class PEKBGGAP_API AFilteringActor : public AActor
{
    GENERATED_BODY()

public:
    AFilteringActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UFilteringManager* Manager;
};

