// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MemoryCategorizationManager.generated.h"

USTRUCT(BlueprintType)
struct FMemoryData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryCategorization")
    TArray<double> Features; // Data features

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryCategorization")
    int32 Category = -1; // Assigned category

    FMemoryData() {}
    FMemoryData(const TArray<double>& InFeatures, int32 InCategory)
        : Features(InFeatures), Category(InCategory) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UMemoryCategorizationManager : public UObject
{
    GENERATED_BODY()

public:
    // Neural network
    UFUNCTION(BlueprintCallable, Category = "MemCat|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "MemCat|Data")
    void AddMemoryData(const TArray<double>& Features, int32 Category);

    UFUNCTION(BlueprintCallable, Category = "MemCat|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "MemCat|NN")
    int32 PredictCategory(const TArray<double>& Features) const;

    // Category statistics: percentage per category key
    UFUNCTION(BlueprintCallable, Category = "MemCat|Stats")
    TMap<int32, double> GetCategoryStatistics() const;

private:
    // Dataset
    UPROPERTY()
    TArray<FMemoryData> MemoryEntries;

    // NN dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0;

    // NN parameters
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

