// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MemoryPreprocessingSpeedManager.generated.h"

USTRUCT(BlueprintType)
struct FMemoryPreprocessingData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preprocessing")
    TArray<double> Features; // task characteristics

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preprocessing")
    double PreprocessingTime = 0.0; // microseconds

    FMemoryPreprocessingData() {}
    FMemoryPreprocessingData(const TArray<double>& InFeatures, double InTime)
        : Features(InFeatures), PreprocessingTime(InTime) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UMemoryPreprocessingSpeedManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Preprocessing|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Preprocessing|Data")
    void AddPreprocessingData(const TArray<double>& Features, double PreprocessingTime);

    UFUNCTION(BlueprintCallable, Category = "Preprocessing|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Preprocessing|NN")
    double PredictPreprocessingTime(const TArray<double>& Features) const;

    UFUNCTION(BlueprintCallable, Category = "Preprocessing|Stats")
    double CalculateAveragePreprocessingTime() const;

private:
    // Dataset
    UPROPERTY()
    TArray<FMemoryPreprocessingData> Entries;

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
