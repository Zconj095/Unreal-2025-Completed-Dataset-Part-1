#include "SolarSynapticAdaptationComponent.h"

#include "Math/UnrealMathUtility.h"

USolarSynapticAdaptationComponent::USolarSynapticAdaptationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarSynapticAdaptationComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeElapsed = 0.0f;
}

void USolarSynapticAdaptationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimeElapsed += DeltaTime;
    const float Adaptability = CalculateSynapticAdaptability(TimeElapsed);
    UE_LOG(LogTemp, Log, TEXT("Time: %.2fs, Synaptic Adaptability (S_s): %.4f"), TimeElapsed, Adaptability);
}

float USolarSynapticAdaptationComponent::CalculateSynapticAdaptability(float Time) const
{
    const float Oscillation = FMath::Sin(2.0f * PI * SolarFrequency * Time);
    return BaselineConnectivity * (1.0f + Sensitivity * SolarIntensity * Oscillation);
}
