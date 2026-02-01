// Demo actor for LearningRateAcknowledgmentManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningRateAcknowledgmentManager.h"
#include "LearningRateAcknowledgmentActor.generated.h"

UCLASS()
class PEKBGGAP_API ALearningRateAcknowledgmentActor : public AActor
{
    GENERATED_BODY()

public:
    ALearningRateAcknowledgmentActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ULearningRateAcknowledgmentManager* Manager;
};

