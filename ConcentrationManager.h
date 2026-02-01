// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConcentrationManager.generated.h"

USTRUCT(BlueprintType)
struct FConcentrationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Concentration")
    double Focus = 0.0; // F

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Concentration")
    double Distraction = 0.0; // D

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Concentration")
    double Susceptibility = 0.0; // sigma

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Concentration")
    double Concentration = 0.0; // Con

    FConcentrationData() {}
    FConcentrationData(double InF, double InD, double InS, double InCon)
        : Focus(InF), Distraction(InD), Susceptibility(InS), Concentration(InCon) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UConcentrationManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Concentration|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Concentration|Data")
    void AddConcentrationData(double Focus, double Distraction, double Susceptibility);

    UFUNCTION(BlueprintCallable, Category = "Concentration|Calc")
    double CalculateConcentration(double Focus, double Distraction, double Susceptibility) const;

    UFUNCTION(BlueprintCallable, Category = "Concentration|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Concentration|NN")
    double PredictConcentration(double Focus, double Distraction, double Susceptibility) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FConcentrationData> Dataset;

    // NN dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0; // expected 1

    // Parameters
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

