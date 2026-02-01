// Demo actor for RetrievalRateManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RetrievalRateManager.h"
#include "RetrievalRateActor.generated.h"

UCLASS()
class PEKBGGAP_API ARetrievalRateActor : public AActor
{
    GENERATED_BODY()

public:
    ARetrievalRateActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    URetrievalRateManager* Manager;

    void AddRetrievalEntryWithTiming(const TArray<double>& Features, bool bIsRetrieved, float RetrievalTime);
};

