// Demo actor for UDifferentiationManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DifferentiationManager.h"
#include "DifferentiationActor.generated.h"

UCLASS()
class PEKBGGAP_API ADifferentiationActor : public AActor
{
    GENERATED_BODY()

public:
    ADifferentiationActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UDifferentiationManager* Manager;
};

