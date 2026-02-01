#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarPredictionAnalysisComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarPredictionAnalysisComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarPredictionAnalysisComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Prediction")
    float Mu = 0.0f;

    UPROPERTY(EditAnywhere, Category="Prediction")
    float Sigma = 1.0f;

    UPROPERTY(EditAnywhere, Category="Prediction")
    float ObservationPeriod = 10.0f;

    UPROPERTY(EditAnywhere, Category="Prediction", meta=(ClampMin="1"))
    int32 Steps = 100;

    float CalculatePredictionCapacity() const;
    float GaussianFunction(float X) const;
};
