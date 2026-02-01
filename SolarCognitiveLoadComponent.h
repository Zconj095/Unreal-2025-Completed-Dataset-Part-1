#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarCognitiveLoadComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarCognitiveLoadComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarCognitiveLoadComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Input Parameters")
    float ProcessingTimeConstant = 1.0f;

    UPROPERTY(EditAnywhere, Category="Input Parameters")
    float EnvironmentalStimuli = 1.0f;

    UPROPERTY(EditAnywhere, Category="Input Parameters")
    float RadiativeStimuli = 1.0f;

    UPROPERTY(EditAnywhere, Category="Input Parameters")
    float TimeStep = 0.01f;

    UPROPERTY(VisibleInstanceOnly, Category="Output")
    float SolarCognitiveLoad = 0.0f;

    float CumulativeSum = 0.0f;
    float LastUpdateTime = 0.0f;

    float InteractionFunction(float Es, float Rs) const;
};
