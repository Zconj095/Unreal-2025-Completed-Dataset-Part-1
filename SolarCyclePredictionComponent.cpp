#include "SolarCyclePredictionComponent.h"

#include "Math/UnrealMathUtility.h"

USolarCyclePredictionComponent::USolarCyclePredictionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USolarCyclePredictionComponent::BeginPlay()
{
    Super::BeginPlay();
    const float Result = PredictAmplitude(Amplitude, Period, PhaseOffset, Time);
    UE_LOG(LogTemp, Log, TEXT("Predicted Solar Activity Amplitude (A(t)): %.4f"), Result);
}

float USolarCyclePredictionComponent::PredictAmplitude(float A0, float T, float Phi, float TimeValue) const
{
    if (FMath::IsNearlyZero(T))
    {
        UE_LOG(LogTemp, Warning, TEXT("Period (T) must be non-zero."));
        return 0.0f;
    }

    return A0 * FMath::Sin((2.0f * PI * TimeValue / T) + Phi);
}
