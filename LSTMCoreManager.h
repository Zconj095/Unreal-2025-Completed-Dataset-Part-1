// Converted from Unity C# to Unreal C++ (feedforward stand-in for LSTM)
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LSTMCoreManager.generated.h"

USTRUCT(BlueprintType)
struct FLSTMSequence
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSTM")
    TArray<double> Input;  // size = InputSize

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LSTM")
    TArray<double> Output; // size = OutputSize

    FLSTMSequence() {}
    FLSTMSequence(const TArray<double>& In, const TArray<double>& Out)
        : Input(In), Output(Out) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API ULSTMMemoryManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LSTM|NN")
    void InitializeLSTM(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "LSTM|Data")
    void AddMemorySequence(const TArray<double>& Input, const TArray<double>& Output);

    UFUNCTION(BlueprintCallable, Category = "LSTM|NN")
    double TrainLSTM(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "LSTM|NN")
    TArray<double> PredictSequence(const TArray<double>& Input) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FLSTMSequence> Sequences;

    // Network dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0;

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

