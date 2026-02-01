// Demo actor for ConcentrationManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConcentrationManager.h"
#include "ConcentrationActor.generated.h"

UCLASS()
class PEKBGGAP_API AConcentrationActor : public AActor
{
    GENERATED_BODY()

public:
    AConcentrationActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UConcentrationManager* Manager;
};

