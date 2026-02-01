// Demo actor for MemoryAllocationSpeedManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryAllocationSpeedManager.h"
#include "MemoryAllocationSpeedActor.generated.h"

UCLASS()
class PEKBGGAP_API AMemoryAllocationSpeedActor : public AActor
{
    GENERATED_BODY()

public:
    AMemoryAllocationSpeedActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMemoryAllocationSpeedManager* Manager;

    void AddAllocationTimer(const TArray<double>& Features);
    void SimulateMemoryAllocation(const TArray<double>& Features);
};

