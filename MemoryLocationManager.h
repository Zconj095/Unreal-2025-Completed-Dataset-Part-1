// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MemoryLocationManager.generated.h"

USTRUCT(BlueprintType)
struct FMemoryLocationEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryLocation")
    FString Id;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryLocation")
    FVector2D Location = FVector2D::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryLocation")
    TArray<double> Features;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MemoryLocation")
    bool bIsAccessed = false;

    FMemoryLocationEntry() {}
    FMemoryLocationEntry(const FString& InId, const FVector2D& InLoc, const TArray<double>& InFeatures, bool bInAccessed)
        : Id(InId), Location(InLoc), Features(InFeatures), bIsAccessed(bInAccessed) {}
};

UCLASS(BlueprintType)
class PEKBGGAP_API UMemoryLocationManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "MemLoc|NN")
    void InitializeNeuralNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "MemLoc|Data")
    void AddMemoryLocation(const FString& Id, const FVector2D& Location, const TArray<double>& Features, bool bIsAccessed);

    UFUNCTION(BlueprintCallable, Category = "MemLoc|Stats")
    double CalculateAccessRate() const;

    UFUNCTION(BlueprintCallable, Category = "MemLoc|Stats")
    FVector2D CalculateAverageLocation() const;

    UFUNCTION(BlueprintCallable, Category = "MemLoc|NN")
    void TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "MemLoc|NN")
    FVector2D PredictOptimalLocation(const TArray<double>& Features) const;

private:
    // Dataset
    UPROPERTY()
    TArray<FMemoryLocationEntry> Entries;

    // NN dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0; // e.g., 2 for XY

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

