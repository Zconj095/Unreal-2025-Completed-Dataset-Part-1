// Demo actor for ComprehensionManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComprehensionManager.h"
#include "ComprehensionActor.generated.h"

UCLASS()
class PEKBGGAP_API AComprehensionActor : public AActor
{
    GENERATED_BODY()

public:
    AComprehensionActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UComprehensionManager* Manager;
};

