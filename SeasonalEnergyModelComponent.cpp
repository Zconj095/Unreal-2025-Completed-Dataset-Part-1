#include "SeasonalEnergyModelComponent.h"

#include "Math/UnrealMathUtility.h"

USeasonalEnergyModelComponent::USeasonalEnergyModelComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

double USeasonalEnergyModelComponent::CalculateSeasonalEnergy(double Amplitude, double Period, double PhaseShift, double Time)
{
    const double TwoPi = 2.0 * PI;
    return Amplitude * FMath::Sin((TwoPi * Time / Period) + PhaseShift);
}

void USeasonalEnergyModelComponent::BeginPlay()
{
    Super::BeginPlay();

    const double Amplitude = 10.0;
    const double Period = 365.0;
    const double PhaseShift = PI / 4.0;
    const double TimeValue = 50.0;

    const double Energy = CalculateSeasonalEnergy(Amplitude, Period, PhaseShift, TimeValue);

    UE_LOG(LogTemp, Log, TEXT("Seasonal energy at time t=%.1f: %.6f"), TimeValue, Energy);
}
