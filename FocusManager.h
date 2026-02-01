// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FocusManager.generated.h"

USTRUCT(BlueprintType)
struct FFocusData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Focus")
    double Rc = 0.0; // Resources allocated

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Focus")
    double Tc = 0.0; // Total cognitive load

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Focus")
    double Focus = 0.0; // Calculated focus

    FFocusData() {}
    FFocusData(double InRc, double InTc, double InFocus)
        : Rc(InRc), Tc(InTc), Focus(InFocus) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UFocusManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Focus|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Focus|Data")
    void AddFocusData(double Rc, double Tc);

    UFUNCTION(BlueprintCallable, Category = "Focus|Calc")
    double CalculateFocus(double Rc, double Tc) const;

    UFUNCTION(BlueprintCallable, Category = "Focus|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Focus|NN")
    double PredictFocus(double Rc, double Tc) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FFocusData> Dataset;

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

