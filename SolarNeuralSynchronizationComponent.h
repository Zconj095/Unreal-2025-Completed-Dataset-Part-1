#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarNeuralSynchronizationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarNeuralSynchronizationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarNeuralSynchronizationComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Neural Sync")
    float N0 = 1.0f;

    UPROPERTY(EditAnywhere, Category="Neural Sync")
    float Amplititude = 0.5f;

    UPROPERTY(EditAnywhere, Category="Neural Sync")
    float OmegaS = 2.0f;

    UPROPERTY(EditAnywhere, Category="Neural Sync")
    float Phi = 0.0f;

    float TimeElapsed = 0.0f;

    float CalculateSolarNeuralActivity(float Time) const;
};
