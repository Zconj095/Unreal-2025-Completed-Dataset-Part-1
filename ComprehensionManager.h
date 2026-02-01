// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ComprehensionManager.generated.h"

USTRUCT(BlueprintType)
struct FComprehensionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comprehension")
    double Ip = 0.0; // Processed information

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comprehension")
    double Ic = 0.0; // Total cognitive capacity

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comprehension")
    double FocusFactor = 0.0; // Focus factor

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Comprehension")
    double Comprehension = 0.0; // Calculated comprehension

    FComprehensionData() {}
    FComprehensionData(double InIp, double InIc, double InFocus, double InComp)
        : Ip(InIp), Ic(InIc), FocusFactor(InFocus), Comprehension(InComp) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UComprehensionManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Comprehension|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Comprehension|Data")
    void AddComprehensionData(double Ip, double Ic, double FocusFactor);

    UFUNCTION(BlueprintCallable, Category = "Comprehension|Calc")
    double CalculateComprehension(double Ip, double Ic, double FocusFactor) const;

    UFUNCTION(BlueprintCallable, Category = "Comprehension|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Comprehension|NN")
    double PredictComprehension(double Ip, double Ic, double FocusFactor) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FComprehensionData> Dataset;

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

