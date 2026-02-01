#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticOscillationsComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticOscillationsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticOscillationsComponent();

    UFUNCTION(BlueprintCallable, Category="Synaptic Oscillation")
    void UpdateParameters(float NewAmplitude, float NewFrequency, float NewPhaseOffset);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Oscillation")
    float Amplitude = 1.0f;

    UPROPERTY(EditAnywhere, Category="Oscillation")
    float Frequency = 1.0f;

    UPROPERTY(EditAnywhere, Category="Oscillation")
    float PhaseOffset = 0.0f;

    float SynapticOscillation = 0.0f;

    float CalculateOscillation(float Time) const;
};
