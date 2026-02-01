#include "SynapticAdaptationEfficiencyComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticAdaptationEfficiencyComponent::USynapticAdaptationEfficiencyComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USynapticAdaptationEfficiencyComponent::BeginPlay()
{
    Super::BeginPlay();

    const float Energy = CalculateEnergyPerSynapticOperation(BoltzmannConstant, BrainTemperature, AdaptationEfficiency);
    UE_LOG(LogTemp, Log, TEXT("Energy per Synaptic Operation (E_s): %.8f J"), Energy);
}

float USynapticAdaptationEfficiencyComponent::CalculateEnergyPerSynapticOperation(float Kb, float T, float Nu) const
{
    constexpr float LnTwo = 0.693147f;
    return (Kb * T / LnTwo) * Nu;
}
