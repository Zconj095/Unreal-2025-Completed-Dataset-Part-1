#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataArrayWrappers.h"
#include "SpecialMagicalEnergyPredictorComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USpecialMagicalEnergyPredictorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USpecialMagicalEnergyPredictorComponent();

    /** Forward pass prediction (zero-indexed temperature vector). */
    UFUNCTION(BlueprintCallable, Category="Magical Energy")
    TArray<double> Predict(const TArray<double>& Inputs) const;

    /** Train the simple network using stochastic gradient descent. */
    UFUNCTION(BlueprintCallable, Category="Magical Energy")
    void Train(const TArray<FDoubleArrayWrapper>& Inputs, const TArray<FDoubleArrayWrapper>& Targets, int32 Epochs, double LearningRate);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Magical Energy")
    int32 InputSize = 1;

    UPROPERTY(EditAnywhere, Category="Magical Energy")
    int32 HiddenSize = 10;

    UPROPERTY(EditAnywhere, Category="Magical Energy")
    int32 OutputSize = 2;

    UPROPERTY()
    TArray<double> InputToHiddenWeights; // HiddenSize * InputSize

    UPROPERTY()
    TArray<double> HiddenBias;

    UPROPERTY()
    TArray<double> HiddenToOutputWeights; // OutputSize * HiddenSize

    UPROPERTY()
    TArray<double> OutputBias;

    mutable TArray<double> HiddenLayerValues;

    void InitializeNetwork();
    double Sigmoid(double Value) const;
    void Forward(const TArray<double>& Inputs, TArray<double>& OutOutputs) const;
};
