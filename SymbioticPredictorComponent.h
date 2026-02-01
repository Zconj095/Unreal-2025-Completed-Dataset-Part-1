#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymbioticPredictorComponent.generated.h"

USTRUCT(BlueprintType)
struct FSymbioticSample
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TArray<double> Inputs;

    UPROPERTY(EditAnywhere)
    TArray<double> Targets;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymbioticPredictorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymbioticPredictorComponent();

    UFUNCTION(BlueprintCallable, Category="Symbiosis")
    void InitializeNetwork(int32 InputSize = 2, int32 HiddenSize = 10, int32 OutputSize = 1);

    UFUNCTION(BlueprintCallable, Category="Symbiosis")
    TArray<double> Predict(const TArray<double>& Inputs);

    UFUNCTION(BlueprintCallable, Category="Symbiosis")
    void Train(const TArray<FSymbioticSample>& Dataset, int32 Epochs, double LearningRate);

protected:
    virtual void BeginPlay() override;

private:
    int32 InputSize = 2;
    int32 HiddenSize = 10;
    int32 OutputSize = 1;

    TArray<double> InputToHiddenWeights;
    TArray<double> HiddenBias;
    TArray<double> HiddenToOutputWeights;
    TArray<double> OutputBias;
    TArray<double> HiddenValues;

    void AllocateParameters();
    double Sigmoid(double Value) const;
    void Forward(const TArray<double>& Inputs, TArray<double>& Outputs);
};
