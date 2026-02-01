#include "SolarCycleVisualizerComponent.h"

#include "Components/TextRenderComponent.h"
#include "Math/UnrealMathUtility.h"

USolarCycleVisualizerComponent::USolarCycleVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USolarCycleVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    const float SolarAmplitude = PredictAmplitude(AmplitudeBase, Period, PhaseOffset, TimeValue);

    if (DisplayText)
    {
        const FString DisplayString = FString::Printf(TEXT("Solar Amplitude: %.2f"), SolarAmplitude);
        DisplayText->SetText(FText::FromString(DisplayString));
    }

    UE_LOG(LogTemp, Log, TEXT("Solar Activity Amplitude: %.2f"), SolarAmplitude);
}

float USolarCycleVisualizerComponent::PredictAmplitude(float A0, float T, float Phi, float Time) const
{
    if (FMath::IsNearlyZero(T))
    {
        UE_LOG(LogTemp, Warning, TEXT("Period (T) must be non-zero."));
        return 0.0f;
    }

    return A0 * FMath::Sin((2.0f * PI * Time / T) + Phi);
}
