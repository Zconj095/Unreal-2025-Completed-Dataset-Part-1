// Demo actor for RecallAndRecollectionManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecallAndRecollectionManager.h"
#include "RecallAndRecollectionActor.generated.h"

UCLASS()
class PEKBGGAP_API ARecallAndRecollectionActor : public AActor
{
    GENERATED_BODY()

public:
    ARecallAndRecollectionActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    URecallAndRecollectionManager* Manager;
};

