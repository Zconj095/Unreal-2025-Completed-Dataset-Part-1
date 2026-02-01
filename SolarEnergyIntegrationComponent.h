#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarEnergyIntegrationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarEnergyIntegrationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarEnergyIntegrationComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Integration")
    float InitialTime = 0.0f;

    UPROPERTY(EditAnywhere, Category="Integration")
    float CurrentTime = 0.0f;

    UPROPERTY(EditAnywhere, Category="Integration")
    float TimeStep = 0.01f;

    UPROPERTY(EditAnywhere, Category="Integration")
    float EnvironmentParameter = 1.0f;

    UPROPERTY(VisibleInstanceOnly, Category="Integration")
    float SolarEnergyIntegrated = 0.0f;

    float CalculateSEI(float Start, float End, float Delta, float Parameter) const;
    float SolarEnergyFlux(float Parameter, float Time) const;
};
