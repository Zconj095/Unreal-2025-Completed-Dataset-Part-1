// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CategorizedDataRetrievalLibrary.h"
#include "InclusionExclusionManager.generated.h"

USTRUCT(BlueprintType)
struct FInclusionExclusionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IncludeExclude")
    TArray<double> OriginalData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IncludeExclude")
    TArray<double> Included;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IncludeExclude")
    TArray<double> Excluded;

    FInclusionExclusionData() {}
    FInclusionExclusionData(const TArray<double>& InOriginal, const TArray<double>& InIncluded, const TArray<double>& InExcluded)
        : OriginalData(InOriginal), Included(InIncluded), Excluded(InExcluded) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UInclusionExclusionManager : public UObject
{
    GENERATED_BODY()

public:
    // NN
    UFUNCTION(BlueprintCallable, Category = "IncludeExclude|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "IncludeExclude|NN")
    void TrainNetwork(const TArray<FDoubleArray>& Inputs, const TArray<FDoubleArray>& Outputs, int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "IncludeExclude|NN")
    FString Predict(const TArray<double>& Input) const;

    // Separation
    TTuple<TArray<double>, TArray<double>> Separate(const TArray<double>& Data, TFunctionRef<bool(double)> DecisionFunction) const;

    void AddInclusionExclusionData(const TArray<double>& Data, TFunctionRef<bool(double)> DecisionFunction);

    UFUNCTION(BlueprintCallable, Category = "IncludeExclude|Data")
    void DisplayResults() const;

private:
    // Data entries
    UPROPERTY()
    TArray<FInclusionExclusionData> Entries;

    // NN dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0;

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
