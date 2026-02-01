// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CategorizedDataRetrievalLibrary.h"
#include "FilteringManager.generated.h"

USTRUCT(BlueprintType)
struct FFilteredData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filtering")
    TArray<double> OriginalData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Filtering")
    TArray<double> FilteredResults;

    FFilteredData() {}
    FFilteredData(const TArray<double>& InOriginal, const TArray<double>& InFiltered)
        : OriginalData(InOriginal), FilteredResults(InFiltered) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UFilteringManager : public UObject
{
    GENERATED_BODY()

public:
    // NN
    UFUNCTION(BlueprintCallable, Category = "Filtering|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Filtering|NN")
    void TrainNetwork(const TArray<FDoubleArray>& Inputs, const TArray<FDoubleArray>& Outputs, int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Filtering|NN")
    double Predict(const TArray<double>& Input) const;

    // Filtering
    TArray<double> Filter(const TArray<double>& Data, TFunctionRef<bool(double)> Predicate) const;

    void AddFilteringData(const TArray<double>& Data, TFunctionRef<bool(double)> Predicate);

    UFUNCTION(BlueprintCallable, Category = "Filtering|Data")
    void DisplayFilteredResults() const;

private:
    // Data entries
    UPROPERTY()
    TArray<FFilteredData> FilteredDataEntries;

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
