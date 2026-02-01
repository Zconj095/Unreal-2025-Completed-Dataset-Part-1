#include "SolarEnergyResonanceComponent.h"

#include "Math/UnrealMathUtility.h"

USolarEnergyResonanceComponent::USolarEnergyResonanceComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarEnergyResonanceComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USolarEnergyResonanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentTime += DeltaTime;
    ResonanceFactor = CalculateSER(Amplitude, CyclePeriod, CurrentTime);

    UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Solar-Energy Resonance (Rs): %.2f"), CurrentTime, ResonanceFactor);
}

float USolarEnergyResonanceComponent::CalculateSER(float A, float P, float Time) const
{
    if (P <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Solar radiation cycle period (P) must be greater than zero."));
        return 0.0f;
    }

    return A * FMath::Cos((2.0f * PI * Time) / P);
}
