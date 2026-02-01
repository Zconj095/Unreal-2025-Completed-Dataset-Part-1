#include "SimilarityManager.h"

void USimilarityManager::InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize;
    // Unity version randomized weights but never used the network; we store dims for parity.
}

double USimilarityManager::CalculateCosineSimilarity(const TArray<double>& VectorX, const TArray<double>& VectorY) const
{
    if (VectorX.Num() != VectorY.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Vectors must have the same length to calculate cosine similarity."));
        return 0.0;
    }
    double Dot = 0.0;
    double MagX2 = 0.0;
    double MagY2 = 0.0;
    for (int32 i = 0; i < VectorX.Num(); ++i)
    {
        const double x = VectorX[i];
        const double y = VectorY[i];
        Dot += x * y;
        MagX2 += x * x;
        MagY2 += y * y;
    }
    if (MagX2 == 0.0 || MagY2 == 0.0)
    {
        UE_LOG(LogTemp, Error, TEXT("One or both vectors have zero magnitude."));
        return 0.0;
    }
    return Dot / (FMath::Sqrt(MagX2) * FMath::Sqrt(MagY2));
}

double USimilarityManager::CalculateEuclideanDistance(const TArray<double>& VectorX, const TArray<double>& VectorY) const
{
    if (VectorX.Num() != VectorY.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Vectors must have the same length to calculate Euclidean distance."));
        return TNumericLimits<double>::Max();
    }
    double Sum = 0.0;
    for (int32 i = 0; i < VectorX.Num(); ++i)
    {
        const double d = VectorX[i] - VectorY[i];
        Sum += d * d;
    }
    return FMath::Sqrt(Sum);
}

void USimilarityManager::AddSimilarityData(const TArray<double>& VectorX, const TArray<double>& VectorY)
{
    const double Cos = CalculateCosineSimilarity(VectorX, VectorY);
    Entries.Add(FSimilarityData(VectorX, VectorY, Cos));
}

void USimilarityManager::DisplaySimilarities() const
{
    for (const FSimilarityData& E : Entries)
    {
        FString XStr, YStr;
        for (int32 i = 0; i < E.VectorX.Num(); ++i)
        {
            XStr += FString::SanitizeFloat(E.VectorX[i]);
            if (i + 1 < E.VectorX.Num()) XStr += TEXT(", ");
        }
        for (int32 i = 0; i < E.VectorY.Num(); ++i)
        {
            YStr += FString::SanitizeFloat(E.VectorY[i]);
            if (i + 1 < E.VectorY.Num()) YStr += TEXT(", ");
        }
        UE_LOG(LogTemp, Log, TEXT("VectorX: %s"), *XStr);
        UE_LOG(LogTemp, Log, TEXT("VectorY: %s"), *YStr);
        UE_LOG(LogTemp, Log, TEXT("Cosine Similarity: %f"), E.CosineSimilarity);
    }
}

