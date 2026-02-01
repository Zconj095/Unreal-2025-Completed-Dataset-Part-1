#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarEclipseNeuralSynchronizationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarEclipseNeuralSynchronizationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarEclipseNeuralSynchronizationComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Solar Eclipse")
    float MoonShadowRadius = 1.0f;

    UPROPERTY(EditAnywhere, Category="Solar Eclipse")
    float EclipseRange = 10.0f;

    UPROPERTY(EditAnywhere, Category="Solar Eclipse")
    float EclipseEnergyFlux = 1.0f;

    float NeuralSynchronization = 0.0f;

    float CalculateSENS(float Rm, float Rt, float Phi) const;
};
