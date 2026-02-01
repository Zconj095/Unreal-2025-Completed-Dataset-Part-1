// Demo actor for SpatialLSTMManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpatialLSTMManager.h"
#include "SpatialLSTMActor.generated.h"

UCLASS()
class PEKBGGAP_API ASpatialLSTMActor : public AActor
{
    GENERATED_BODY()

public:
    ASpatialLSTMActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USpatialLSTMManager* Manager;
};

