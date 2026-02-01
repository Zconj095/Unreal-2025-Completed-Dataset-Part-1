// Demo actor for FocusManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FocusManager.h"
#include "FocusActor.generated.h"

UCLASS()
class PEKBGGAP_API AFocusActor : public AActor
{
    GENERATED_BODY()

public:
    AFocusActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UFocusManager* Manager;
};

