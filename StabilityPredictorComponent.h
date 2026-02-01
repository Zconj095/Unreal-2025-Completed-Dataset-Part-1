#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataArrayWrappers.h"
#include "StabilityPredictorComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStabilityPredictorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStabilityPredictorComponent();

    UFUNCTION(BlueprintCallable, Category="Stability")
    TArray<double> Predict(const TArray<double>& Inputs) const;

    UFUNCTION(BlueprintCallable, Category="Stability")
    void Train(const TArray<FDoubleArrayWrapper>& Inputs, const TArray<FDoubleArrayWrapper>& Targets, int32 Epochs, double LearningRate);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Stability")
    int32 InputSize = 2;

    UPROPERTY(EditAnywhere, Category="Stability")
    int32 HiddenSize = 10;

    UPROPERTY(EditAnywhere, Category="Stability")
    int32 OutputSize = 1;

    TArray<double> InputToHiddenWeights;
    TArray<double> HiddenBias;
    TArray<double> HiddenToOutputWeights;
    TArray<double> OutputBias;
    mutable TArray<double> HiddenLayerValues;

    void InitializeNetwork();
    void AllocateWeights();
    double Sigmoid(double Value) const;
    void Forward(const TArray<double>& Inputs, TArray<double>& Outputs) const;
};
