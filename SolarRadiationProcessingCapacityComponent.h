#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarRadiationProcessingCapacityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarRadiationProcessingCapacityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarRadiationProcessingCapacityComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Radiation")
    float EncodingEfficiency = 1.0f;

    UPROPERTY(EditAnywhere, Category="Radiation")
    float MinWavelength = 300.0f;

    UPROPERTY(EditAnywhere, Category="Radiation")
    float MaxWavelength = 700.0f;

    UPROPERTY(EditAnywhere, Category="Radiation", meta=(ClampMin="1"))
    int32 Steps = 100;

    float CalculateSRPC(float Alpha, float LambdaMin, float LambdaMax, int32 StepCount) const;
    float SolarRadiationIntensity(float Lambda) const;
};
