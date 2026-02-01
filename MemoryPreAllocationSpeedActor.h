// Demo actor for MemoryPreAllocationSpeedManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryPreAllocationSpeedManager.h"
#include "MemoryPreAllocationSpeedActor.generated.h"

UCLASS()
class PEKBGGAP_API AMemoryPreAllocationSpeedActor : public AActor
{
    GENERATED_BODY()

public:
    AMemoryPreAllocationSpeedActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMemoryPreAllocationSpeedManager* Manager;

    void AddPreAllocationTimer(const TArray<double>& Features);
    void SimulatePreAllocation(const TArray<double>& Features);
};

