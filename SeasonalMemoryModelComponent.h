#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalMemoryModelComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalMemoryModelComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalMemoryModelComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    float ComputeMemory(float Time) const;

private:
    UPROPERTY(EditAnywhere, Category="Memory Decay")
    float M0 = 100.0f;

    UPROPERTY(EditAnywhere, Category="Memory Decay")
    float Lambda = 0.1f;

    UPROPERTY(EditAnywhere, Category="Encoding Boost")
    float DeltaM = 50.0f;

    UPROPERTY(EditAnywhere, Category="Encoding Boost")
    float Alpha = 0.5f;

    UPROPERTY(EditAnywhere, Category="Encoding Boost")
    float PeakTime = 5.0f;

    UPROPERTY(EditAnywhere, Category="Simulation")
    float SimulationDuration = 10.0f;

    UPROPERTY(EditAnywhere, Category="Simulation")
    int32 Resolution = 100;

    float StartTime = 0.0f;
    void DrawMemoryCurve() const;
};
