#include "SolarPredictionAnalysisComponent.h"

#include "Math/UnrealMathUtility.h"

USolarPredictionAnalysisComponent::USolarPredictionAnalysisComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USolarPredictionAnalysisComponent::BeginPlay()
{
    Super::BeginPlay();

    const float PredictionCapacity = CalculatePredictionCapacity();
    UE_LOG(LogTemp, Log, TEXT("Prediction Capacity (P_s): %.4f"), PredictionCapacity);
}

float USolarPredictionAnalysisComponent::CalculatePredictionCapacity() const
{
    if (Steps <= 0 || ObservationPeriod <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Observation period and steps must be positive."));
        return 0.0f;
    }

    const float DeltaX = ObservationPeriod / static_cast<float>(Steps);
    float Sum = 0.0f;

    for (int32 Index = 0; Index <= Steps; ++Index)
    {
        const float X = Index * DeltaX;
        const float Weight = (Index == 0 || Index == Steps) ? 0.5f : 1.0f;
        Sum += Weight * GaussianFunction(X);
    }

    return Sum * DeltaX;
}

float USolarPredictionAnalysisComponent::GaussianFunction(float X) const
{
    if (FMath::IsNearlyZero(Sigma))
    {
        UE_LOG(LogTemp, Warning, TEXT("Sigma must be non-zero for Gaussian computation."));
        return 0.0f;
    }

    const float Variance = Sigma * Sigma;
    const float Exponent = -FMath::Square(X - Mu) / (2.0f * Variance);
    return (1.0f / FMath::Sqrt(2.0f * PI * Variance)) * FMath::Exp(Exponent);
}
