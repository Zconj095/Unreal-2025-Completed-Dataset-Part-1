#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticBiosyntheticOscillationsComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticBiosyntheticOscillationsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticBiosyntheticOscillationsComponent();

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

    float ElapsedTime = 0.0f;
    float OscillationValue = 0.0f;

    float CalculateOscillation(float Time) const;
};
