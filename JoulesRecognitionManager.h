// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "JoulesRecognitionManager.generated.h"

USTRUCT(BlueprintType)
struct FMemoryOperation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joules")
    TArray<double> Features; // Characteristics of the memory operation

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joules")
    double JoulesConsumed = 0.0; // Energy consumed in Joules

    FMemoryOperation() {}
    FMemoryOperation(const TArray<double>& InFeatures, double InJoules)
        : Features(InFeatures), JoulesConsumed(InJoules) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UJoulesRecognitionManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Joules|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Joules|Data")
    void AddMemoryOperation(const TArray<double>& Features, double JoulesConsumed);

    UFUNCTION(BlueprintCallable, Category = "Joules|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Joules|NN")
    double PredictJoules(const TArray<double>& Features) const;

    UFUNCTION(BlueprintCallable, Category = "Joules|Stats")
    double CalculateAverageJoules() const;

private:
    // Dataset
    UPROPERTY()
    TArray<FMemoryOperation> MemoryOperations;

    // Network dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0; // expected 1

    // Parameters (flattened row-major): W1[Hidden x Input], b1[Hidden], W2[Output x Hidden], b2[Output]
    TArray<double> W1;
    TArray<double> b1;
    TArray<double> W2;
    TArray<double> b2;

    // Helpers
    static double Sigmoid(double x);
    static double SigmoidDerivFromActivation(double a);
    void RandomizeParams(double Scale);
    void ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const;
};

