// Demo actor for NanoMeasurementSpeedTimersManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NanoMeasurementSpeedTimersManager.h"
#include "NanoMeasurementSpeedTimersActor.generated.h"

UCLASS()
class PEKBGGAP_API ANanoMeasurementSpeedTimersActor : public AActor
{
    GENERATED_BODY()

public:
    ANanoMeasurementSpeedTimersActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UNanoMeasurementSpeedTimersManager* Manager;

    void AddOperationTimer(const TArray<double>& Features);
    void SimulateOperation(const TArray<double>& Features);
};

