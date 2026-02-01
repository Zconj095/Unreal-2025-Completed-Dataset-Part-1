#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalNeuralResonanceComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalNeuralResonanceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalNeuralResonanceComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Neural Resonance")
    TArray<float> Amplitudes;

    UPROPERTY(EditAnywhere, Category="Neural Resonance")
    TArray<float> Frequencies;

    UPROPERTY(EditAnywhere, Category="Neural Resonance")
    TArray<float> PhaseShifts;

    float TimeElapsed = 0.0f;

    void UpdateResonance(float DeltaTime);
    double CalculateSeasonalNeuralResonance(float Time) const;
};
