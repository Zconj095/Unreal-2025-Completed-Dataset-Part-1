// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MemoryAllocationSpeedManager.generated.h"

USTRUCT(BlueprintType)
struct FAllocationData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Allocation")
    TArray<double> Features; // characteristics of the allocation op

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Allocation")
    double AllocationTime = 0.0; // microseconds

    FAllocationData() {}
    FAllocationData(const TArray<double>& InFeatures, double InTime)
        : Features(InFeatures), AllocationTime(InTime) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UMemoryAllocationSpeedManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Allocation|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Allocation|Data")
    void AddAllocationData(const TArray<double>& Features, double AllocationTime);

    UFUNCTION(BlueprintCallable, Category = "Allocation|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Allocation|NN")
    double PredictAllocationTime(const TArray<double>& Features) const;

    UFUNCTION(BlueprintCallable, Category = "Allocation|Stats")
    double CalculateAverageAllocationTime() const;

private:
    // Dataset
    UPROPERTY()
    TArray<FAllocationData> Entries;

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

