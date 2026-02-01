// Demo actor for SimilarityManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimilarityManager.h"
#include "SimilarityActor.generated.h"

UCLASS()
class PEKBGGAP_API ASimilarityActor : public AActor
{
    GENERATED_BODY()

public:
    ASimilarityActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    USimilarityManager* Manager;
};

