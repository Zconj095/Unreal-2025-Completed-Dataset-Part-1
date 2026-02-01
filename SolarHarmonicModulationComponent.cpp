#include "SolarHarmonicModulationComponent.h"

#include "Math/UnrealMathUtility.h"

USolarHarmonicModulationComponent::USolarHarmonicModulationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarHarmonicModulationComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeElapsed = 0.0f;
}

void USolarHarmonicModulationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimeElapsed += DeltaTime;
    const float NeuralHarmony = CalculateNeuralHarmony(TimeElapsed);

    UE_LOG(LogTemp, Log, TEXT("Time: %.2f s, Neural Harmony (H_s): %.4f"), TimeElapsed, NeuralHarmony);
}

float USolarHarmonicModulationComponent::CalculateNeuralHarmony(float Time) const
{
    return H0 * (1.0f + Gamma * FMath::Sin(OmegaS * Time + Phi));
}
