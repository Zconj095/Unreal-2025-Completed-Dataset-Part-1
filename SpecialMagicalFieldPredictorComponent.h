#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpecialMagicalFieldPredictorComponent.generated.h"

USTRUCT(BlueprintType)
struct FFieldPredictionSample
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Field Prediction")
    TArray<double> Inputs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Field Prediction")
    TArray<double> Targets;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USpecialMagicalFieldPredictorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USpecialMagicalFieldPredictorComponent();

    UFUNCTION(BlueprintCallable, Category="Magical Field")
    void InitializeNetwork(int32 InInputSize = 1, int32 InHiddenSize = 10, int32 InOutputSize = 3);

    UFUNCTION(BlueprintCallable, Category="Magical Field")
    TArray<double> Predict(const TArray<double>& Inputs) const;

    UFUNCTION(BlueprintCallable, Category="Magical Field")
    void Train(const TArray<FFieldPredictionSample>& Dataset, int32 Epochs, double LearningRate);

protected:
    virtual void BeginPlay() override;

private:
    int32 InputSize = 1;
    int32 HiddenSize = 10;
    int32 OutputSize = 3;

    TArray<double> InputToHiddenWeights;
    TArray<double> HiddenBias;
    TArray<double> HiddenToOutputWeights;
    TArray<double> OutputBias;
    mutable TArray<double> HiddenLayerValues;

    void AllocateWeights();
    double Sigmoid(double Value) const;
    void Forward(const TArray<double>& Inputs, TArray<double>& Outputs) const;
};
