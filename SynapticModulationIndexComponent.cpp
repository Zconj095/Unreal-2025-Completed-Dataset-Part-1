#include "SynapticModulationIndexComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticModulationIndexComponent::USynapticModulationIndexComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USynapticModulationIndexComponent::BeginPlay()
{
    Super::BeginPlay();

    const float SMI = CalculateSMI(Beta, DeltaS, DeltaT);
    UE_LOG(LogTemp, Log, TEXT("Synaptic Modulation Index (SMI): %.4f"), SMI);
}

float USynapticModulationIndexComponent::CalculateSMI(float BetaValue, float DeltaSValue, float DeltaTValue) const
{
    if (FMath::IsNearlyZero(DeltaTValue))
    {
        UE_LOG(LogTemp, Error, TEXT("Time interval (Delta t) cannot be zero!"));
        return 0.0f;
    }

    return BetaValue * (DeltaSValue / DeltaTValue);
}
