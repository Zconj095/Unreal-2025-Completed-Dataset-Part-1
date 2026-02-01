#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalNeuralActivityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalNeuralActivityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalNeuralActivityComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Neural Activity")
    float N0 = 1.0f;

    UPROPERTY(EditAnywhere, Category="Neural Activity")
    float Amplitude = 0.5f;

    UPROPERTY(EditAnywhere, Category="Neural Activity")
    float OmegaJ = 2.0f * PI / 365.0f;

    UPROPERTY(EditAnywhere, Category="Neural Activity")
    float Phi = 0.0f;

    UPROPERTY(EditAnywhere, Category="Simulation")
    float SimulationDuration = 10.0f;

    UPROPERTY(EditAnywhere, Category="Simulation")
    int32 Resolution = 100;

    void DrawSeasonalActivityCurve() const;
    UPROPERTY()
    float StartTime = 0.0f;
};
