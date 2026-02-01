#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarNeuralComplexityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarNeuralComplexityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarNeuralComplexityComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Complexity")
    float InitialComplexity = 1.0f;

    UPROPERTY(EditAnywhere, Category="Complexity")
    float GrowthRate = 0.1f;

    UPROPERTY(VisibleInstanceOnly, Category="Complexity")
    float TimeElapsed = 0.0f;

    UPROPERTY(VisibleInstanceOnly, Category="Complexity")
    float SolarComplexity = 0.0f;

    float CalculateSNC(float Complexity, float Rate, float Time) const;
};
