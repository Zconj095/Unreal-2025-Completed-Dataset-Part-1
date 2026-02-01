#include "SolarEnergyAnalysisComponent.h"

#include "Math/UnrealMathUtility.h"

USolarEnergyAnalysisComponent::USolarEnergyAnalysisComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USolarEnergyAnalysisComponent::BeginPlay()
{
    Super::BeginPlay();

    if (FMath::IsNearlyZero(DistanceFromSun))
    {
        UE_LOG(LogTemp, Warning, TEXT("Distance from sun must not be zero."));
        return;
    }

    const double Intensity = TotalPowerOutput / (4.0 * PI * FMath::Square(DistanceFromSun));
    UE_LOG(LogTemp, Log, TEXT("Solar Intensity (I): %.4f W/m²"), Intensity);
}
