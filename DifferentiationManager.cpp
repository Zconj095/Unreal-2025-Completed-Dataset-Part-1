#include "DifferentiationManager.h"

void UDifferentiationManager::InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize;
    // Note: Network not used further in original script; stored for parity.
}

double UDifferentiationManager::CalculateCosineDissimilarity(const TArray<double>& X, const TArray<double>& Y) const
{
    if (X.Num() != Y.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Vectors must have the same length to calculate cosine dissimilarity."));
        return 0.0;
    }

    double Dot = 0.0;
    double MagX = 0.0;
    double MagY = 0.0;
    for (int i = 0; i < X.Num(); ++i)
    {
        Dot += X[i] * Y[i];
        MagX += X[i] * X[i];
        MagY += Y[i] * Y[i];
    }
    if (MagX == 0.0 || MagY == 0.0)
    {
        UE_LOG(LogTemp, Error, TEXT("One or both vectors have zero magnitude."));
        return 1.0;
    }
    const double CosSim = Dot / (FMath::Sqrt(MagX) * FMath::Sqrt(MagY));
    return 1.0 - CosSim;
}

double UDifferentiationManager::CalculateEuclideanDistance(const TArray<double>& X, const TArray<double>& Y) const
{
    if (X.Num() != Y.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Vectors must have the same length to calculate Euclidean distance."));
        return TNumericLimits<double>::Max();
    }

    double Sum = 0.0;
    for (int i = 0; i < X.Num(); ++i)
    {
        const double d = X[i] - Y[i];
        Sum += d * d;
    }
    return FMath::Sqrt(Sum);
}

FString UDifferentiationManager::VectorToString(const TArray<double>& V)
{
    FString Out;
    for (int i = 0; i < V.Num(); ++i)
    {
        if (i > 0) Out += TEXT(", ");
        Out += FString::SanitizeFloat(V[i]);
    }
    return Out;
}

void UDifferentiationManager::DisplayDifferentiationResults(const TArray<double>& VectorX, const TArray<double>& VectorY) const
{
    const double CosineDissim = CalculateCosineDissimilarity(VectorX, VectorY);
    const double Euclid = CalculateEuclideanDistance(VectorX, VectorY);

    UE_LOG(LogTemp, Log, TEXT("VectorX: %s"), *VectorToString(VectorX));
    UE_LOG(LogTemp, Log, TEXT("VectorY: %s"), *VectorToString(VectorY));
    UE_LOG(LogTemp, Log, TEXT("Cosine Dissimilarity: %f"), CosineDissim);
    UE_LOG(LogTemp, Log, TEXT("Euclidean Distance: %f"), Euclid);
}

