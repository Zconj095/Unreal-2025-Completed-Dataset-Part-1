// Demo actor for ClassificationManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassificationManager.h"
#include "ClassificationActor.generated.h"

UCLASS()
class PEKBGGAP_API AClassificationActor : public AActor
{
    GENERATED_BODY()

public:
    AClassificationActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UClassificationManager* Manager;
};

