#include "SynapticEnergyTransferComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticEnergyTransferComponent::USynapticEnergyTransferComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USynapticEnergyTransferComponent::BeginPlay()
{
    Super::BeginPlay();

    const double SynapticEnergy = CalculateSynapticEnergy(BrainTemperature, QuantumCoherenceEfficiency);
    UE_LOG(LogTemp, Log, TEXT("Synaptic Energy per Operation (E_syn): %.6e J"), SynapticEnergy);
}

double USynapticEnergyTransferComponent::CalculateSynapticEnergy(double Temperature, double QuantumEfficiency) const
{
    if (Temperature <= 0.0 || QuantumEfficiency <= 0.0 || QuantumEfficiency > 1.0)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid parameters: Temperature must be > 0 and 0 < Q <= 1."));
        return 0.0;
    }

    constexpr double BoltzmannConstant = 1.38e-23;
    const double Ln2 = FMath::Loge(2.0f);
    return (BoltzmannConstant * Temperature / Ln2) * QuantumEfficiency;
}
