// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DifferentiationManager.generated.h"

UCLASS(BlueprintType)
class PEKBGGAP_API UDifferentiationManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Differentiation|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    // Cosine Dissimilarity: 1 - cos(x, y)
    UFUNCTION(BlueprintCallable, Category = "Differentiation|Metrics")
    double CalculateCosineDissimilarity(const TArray<double>& VectorX, const TArray<double>& VectorY) const;

    // Euclidean distance
    UFUNCTION(BlueprintCallable, Category = "Differentiation|Metrics")
    double CalculateEuclideanDistance(const TArray<double>& VectorX, const TArray<double>& VectorY) const;

    UFUNCTION(BlueprintCallable, Category = "Differentiation|Display")
    void DisplayDifferentiationResults(const TArray<double>& VectorX, const TArray<double>& VectorY) const;

private:
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0;

    static FString VectorToString(const TArray<double>& V);
};

