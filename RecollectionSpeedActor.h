// Demo actor for RecollectionSpeedManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecollectionSpeedManager.h"
#include "RecollectionSpeedActor.generated.h"

UCLASS()
class PEKBGGAP_API ARecollectionSpeedActor : public AActor
{
    GENERATED_BODY()

public:
    ARecollectionSpeedActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    URecollectionSpeedManager* Manager;

    void AddRecollectionEntryWithTiming(const TArray<double>& Features, float RecallTime, float RetentionTime);
};

