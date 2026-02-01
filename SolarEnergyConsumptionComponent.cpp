#include "SolarEnergyConsumptionComponent.h"

#include "Math/UnrealMathUtility.h"

USolarEnergyConsumptionComponent::USolarEnergyConsumptionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USolarEnergyConsumptionComponent::BeginPlay()
{
    Super::BeginPlay();

    const float TotalEnergy = CalculateEnergyConsumption();
    UE_LOG(LogTemp, Log, TEXT("Total Energy Consumption (E_b): %.4f"), TotalEnergy);
}

float USolarEnergyConsumptionComponent::CalculateEnergyConsumption() const
{
    if (Steps <= 0 || ObservationPeriod <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("ObservationPeriod and Steps must be positive."));
        return 0.0f;
    }

    const float DeltaX = ObservationPeriod / static_cast<float>(Steps);
    float Sum = 0.0f;

    for (int32 Index = 0; Index <= Steps; ++Index)
    {
        const float TimeValue = Index * DeltaX;
        const float Weight = (Index == 0 || Index == Steps) ? 0.5f : 1.0f;
        Sum += Weight * EnergyFunction(TimeValue);
    }

    return Sum * DeltaX;
}

float USolarEnergyConsumptionComponent::EnergyFunction(float Time) const
{
    return BaselineEnergy + SolarEnergy * FMath::Cos(OmegaS * Time);
}
