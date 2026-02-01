// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttentionSpanManager.generated.h"

USTRUCT(BlueprintType)
struct FAttentionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attention")
    double TFocus = 0.0; // Maximum focus time

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attention")
    double D = 0.0; // Distractions

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attention")
    double Lambda = 0.0; // Susceptibility to distractions

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attention")
    double AttentionSpan = 0.0; // Calculated attention span

    FAttentionData() {}
    FAttentionData(double InTFocus, double InD, double InLambda, double InAttentionSpan)
        : TFocus(InTFocus), D(InD), Lambda(InLambda), AttentionSpan(InAttentionSpan) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UAttentionSpanManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Attention|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Attention|Data")
    void AddAttentionData(double TFocus, double D, double Lambda);

    UFUNCTION(BlueprintCallable, Category = "Attention|Calc")
    double CalculateAttentionSpan(double TFocus, double D, double Lambda) const;

    UFUNCTION(BlueprintCallable, Category = "Attention|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Attention|NN")
    double PredictAttentionSpan(double TFocus, double D, double Lambda) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FAttentionData> AttentionDataEntries;

    // Network dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0; // default 1

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

