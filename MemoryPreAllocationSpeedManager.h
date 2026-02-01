// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MemoryPreAllocationSpeedManager.generated.h"

USTRUCT(BlueprintType)
struct FPreAllocationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PreAllocation")
    TArray<double> Features; // characteristics of pre-allocation

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PreAllocation")
    double PreAllocationTime = 0.0; // microseconds

    FPreAllocationData() {}
    FPreAllocationData(const TArray<double>& InFeatures, double InTime)
        : Features(InFeatures), PreAllocationTime(InTime) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UMemoryPreAllocationSpeedManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "PreAllocation|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "PreAllocation|Data")
    void AddPreAllocationData(const TArray<double>& Features, double PreAllocationTime);

    UFUNCTION(BlueprintCallable, Category = "PreAllocation|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "PreAllocation|NN")
    double PredictPreAllocationTime(const TArray<double>& Features) const;

    UFUNCTION(BlueprintCallable, Category = "PreAllocation|Stats")
    double CalculateAveragePreAllocationTime() const;

private:
    // Dataset
    UPROPERTY()
    TArray<FPreAllocationData> Entries;

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

