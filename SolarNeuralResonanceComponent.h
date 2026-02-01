#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarNeuralResonanceComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarNeuralResonanceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarNeuralResonanceComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Resonance")
    float Gamma = 1.0f;

    UPROPERTY(EditAnywhere, Category="Resonance")
    float Lambda = 0.5f;

    UPROPERTY(EditAnywhere, Category="Resonance")
    float FSolar = 0.01f;

    UPROPERTY(EditAnywhere, Category="Resonance")
    float EFluxBase = 10.0f;

    float TimeElapsed = 0.0f;

    float CalculateSolarNeuralResonance(float Time) const;
    float CalculateRadiantFlux(float Time) const;
};
