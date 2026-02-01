// Demo actor for RetainingInformationManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RetainingInformationManager.h"
#include "RetainingInformationActor.generated.h"

UCLASS()
class PEKBGGAP_API ARetainingInformationActor : public AActor
{
    GENERATED_BODY()

public:
    ARetainingInformationActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    URetainingInformationManager* Manager;
};

