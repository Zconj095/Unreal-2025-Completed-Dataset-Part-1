// Demo actor for OrganizingManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrganizingManager.h"
#include "OrganizingActor.generated.h"

UCLASS()
class PEKBGGAP_API AOrganizingActor : public AActor
{
    GENERATED_BODY()

public:
    AOrganizingActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UOrganizingManager* Manager;
};

