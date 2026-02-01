// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttentionListeningAndHearingManager.generated.h"

USTRUCT(BlueprintType)
struct FAuditoryData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auditory")
    double Ia = 0.0; // Intensity of the auditory input

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auditory")
    double Na = 0.0; // Noise level

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auditory")
    double Ht = 0.0; // Threshold intensity for hearing

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Auditory")
    double Al = 0.0; // Calculated auditory attention

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Auditory")
    double H = 0.0;  // Calculated hearing

    FAuditoryData() {}
    FAuditoryData(double InIa, double InNa, double InHt, double InAl, double InH)
        : Ia(InIa), Na(InNa), Ht(InHt), Al(InAl), H(InH) {}
};

/**
 * Lightweight manager with an internal 1-hidden-layer neural net
 * (sigmoid activations, batch gradient descent training).
 */
UCLASS(BlueprintType)
class PEKBGGAP_API UAttentionListeningAndHearingManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Auditory|NN")
    void InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize);

    UFUNCTION(BlueprintCallable, Category = "Auditory|Data")
    void AddAuditoryData(double Ia, double Na, double Ht);

    UFUNCTION(BlueprintCallable, Category = "Auditory|Calc")
    double CalculateAuditoryAttention(double Ia, double Na) const;

    UFUNCTION(BlueprintCallable, Category = "Auditory|Calc")
    double CalculateHearing(double Ia, double Na, double Ht) const;

    UFUNCTION(BlueprintCallable, Category = "Auditory|NN")
    double TrainNetwork(int32 Epochs, double LearningRate = 0.01);

    UFUNCTION(BlueprintCallable, Category = "Auditory|NN")
    void PredictAuditoryResponse(double Ia, double Na, double Ht, double& OutAl, double& OutH) const;

    UFUNCTION(BlueprintCallable, Category = "Auditory|Data")
    const TArray<FAuditoryData>& GetDataset() const { return AuditoryDataEntries; }

private:
    // Dataset
    UPROPERTY()
    TArray<FAuditoryData> AuditoryDataEntries;

    // Network dimensions
    int32 InputSize = 0;
    int32 HiddenSize = 0;
    int32 OutputSize = 0; // fixed to 2 for (Al, H) but kept generic

    // Parameters (flattened row-major): W1[Hidden x Input], b1[Hidden], W2[Output x Hidden], b2[Output]
    TArray<double> W1;
    TArray<double> b1;
    TArray<double> W2;
    TArray<double> b2;

    // Helpers
    static double Sigmoid(double x);
    static double SigmoidDerivFromActivation(double a); // a = sigmoid(x)

    void RandomizeParams(double Scale);
    void ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const;
};

