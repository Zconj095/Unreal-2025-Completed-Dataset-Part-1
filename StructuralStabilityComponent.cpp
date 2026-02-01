#include "StructuralStabilityComponent.h"

#include "Math/UnrealMathUtility.h"

UStructuralStabilityComponent::UStructuralStabilityComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralStabilityComponent::BeginPlay()
{
    Super::BeginPlay();
    EvaluateStress();
}

void UStructuralStabilityComponent::EvaluateStress() const
{
    const float Stress = CalculateStress(Force, Area);
    if (Stress >= 0.0f)
    {
        UE_LOG(LogTemp, Log, TEXT("Stress Experienced (σ): %.4f"), Stress);
    }
}

float UStructuralStabilityComponent::CalculateStress(float ForceValue, float AreaValue) const
{
    if (FMath::IsNearlyZero(AreaValue))
    {
        UE_LOG(LogTemp, Error, TEXT("Cross-sectional area (A) cannot be zero!"));
        return -1.0f;
    }

    return ForceValue / AreaValue;
}
