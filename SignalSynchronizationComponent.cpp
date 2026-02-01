#include "SignalSynchronizationComponent.h"

#include "Math/UnrealMathUtility.h"

USignalSynchronizationComponent::USignalSynchronizationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USignalSynchronizationComponent::BeginPlay()
{
    Super::BeginPlay();

    const float SynchronizationEfficiency = CalculateSynchronizationEfficiency(DeltaB, DeltaM, MagicalEnergy, DeltaT);
    UE_LOG(LogTemp, Log, TEXT("Synchronization Efficiency (ηs): %.4f"), SynchronizationEfficiency);
}

float USignalSynchronizationComponent::CalculateSynchronizationEfficiency(float DeltaBValue, float DeltaMValue, float MagicalEnergyValue, float DeltaTValue) const
{
    if (FMath::IsNearlyZero(DeltaTValue))
    {
        UE_LOG(LogTemp, Error, TEXT("ΔT (signal transmission time) cannot be zero!"));
        return 0.0f;
    }

    return (DeltaBValue + DeltaMValue + MagicalEnergyValue) / DeltaTValue;
}
