#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeasonalEnergyNeuralModelComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USeasonalEnergyNeuralModelComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USeasonalEnergyNeuralModelComponent();

    double Predict(double Time) const;

protected:
    virtual void BeginPlay() override;

private:
    void InitializeNetwork();
    double Sigmoid(double Value) const;

    static constexpr int32 HiddenLayerNeuronCount = 10;

    double HiddenWeights[HiddenLayerNeuronCount];
    double HiddenBias[HiddenLayerNeuronCount];
    double OutputWeights[HiddenLayerNeuronCount];
    double OutputBias;
};
