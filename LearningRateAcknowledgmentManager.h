// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LearningRateAcknowledgmentManager.generated.h"

USTRUCT(BlueprintType)
struct FLearningData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningRate")
    double DeltaK = 0.0; // Knowledge gained

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningRate")
    double DeltaT = 0.0; // Time spent learning

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LearningRate")
    double LearningRate = 0.0; // DeltaK / DeltaT

    FLearningData() {}
    FLearningData(double InDeltaK, double InDeltaT, double InLR)
        : DeltaK(InDeltaK), DeltaT(InDeltaT), LearningRate(InLR) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API ULearningRateAcknowledgmentManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LearningRate|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "LearningRate|Data")
    void AddLearningData(double DeltaK, double DeltaT);

    UFUNCTION(BlueprintCallable, Category = "LearningRate|Calc")
    double CalculateLearningRate(double DeltaK, double DeltaT) const;

    UFUNCTION(BlueprintCallable, Category = "LearningRate|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "LearningRate|NN")
    double PredictLearningRate(double DeltaK, double DeltaT) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FLearningData> Dataset;

    // NN dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0; // expected 1

    // Parameters (flattened row-major)
    TArray<double> W1; // Hidden x Input
    TArray<double> b1; // Hidden
    TArray<double> W2; // Output x Hidden
    TArray<double> b2; // Output

    // Helpers
    static double Sigmoid(double x);
    static double SigmoidDerivFromActivation(double a);
    void RandomizeParams(double Scale);
    void ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const;
};

