// Demo actor for MemoryPreprocessingSpeedManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryPreprocessingSpeedManager.h"
#include "MemoryPreprocessingSpeedActor.generated.h"

UCLASS()
class PEKBGGAP_API AMemoryPreprocessingSpeedActor : public AActor
{
    GENERATED_BODY()

public:
    AMemoryPreprocessingSpeedActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMemoryPreprocessingSpeedManager* Manager;

    void AddPreprocessingTimer(const TArray<double>& Features);
    void SimulatePreprocessing(const TArray<double>& Features);
};

