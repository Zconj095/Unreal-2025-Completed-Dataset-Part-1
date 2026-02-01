#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpecialMutationRateVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USpecialMutationRateVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USpecialMutationRateVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    float Lambda = 1.0f;

    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    float EnergyBarrier = 0.5f;

    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    float TemperatureStart = 290.0f;

    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    float TemperatureEnd = 310.0f;

    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    float TemperatureStep = 1.0f;

    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    float MagicalFactor = 0.1f;

    UPROPERTY(EditAnywhere, Category="Mutation Visualization")
    TSubclassOf<AActor> PointActorClass;

    float CalculateMutationRate(float LambdaValue, float Barrier, float Temperature, float MagicalBoost) const;
};
