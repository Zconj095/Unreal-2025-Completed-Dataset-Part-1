// Demo actor for MicroMeasurementSpeedTimersManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MicroMeasurementSpeedTimersManager.h"
#include "MicroMeasurementSpeedTimersActor.generated.h"

UCLASS()
class PEKBGGAP_API AMicroMeasurementSpeedTimersActor : public AActor
{
    GENERATED_BODY()

public:
    AMicroMeasurementSpeedTimersActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMicroMeasurementSpeedTimersManager* Manager;

    void AddOperationTimer(const TArray<double>& Features);
    void SimulateOperation(const TArray<double>& Features);
};

