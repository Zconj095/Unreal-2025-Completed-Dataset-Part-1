// Demo actor for InclusionExclusionManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InclusionExclusionManager.h"
#include "InclusionExclusionActor.generated.h"

UCLASS()
class PEKBGGAP_API AInclusionExclusionActor : public AActor
{
    GENERATED_BODY()

public:
    AInclusionExclusionActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UInclusionExclusionManager* Manager;
};

