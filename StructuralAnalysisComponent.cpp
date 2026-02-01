#include "StructuralAnalysisComponent.h"

#include "Math/UnrealMathUtility.h"

UStructuralAnalysisComponent::UStructuralAnalysisComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralAnalysisComponent::BeginPlay()
{
    Super::BeginPlay();
    EvaluateStress();
}

void UStructuralAnalysisComponent::EvaluateStress() const
{
    if (Area <= 0.0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cross-sectional area must be greater than zero."));
        return;
    }

    const double Stress = Force / Area;
    UE_LOG(LogTemp, Log, TEXT("Stress on component: %.4f Pa"), Stress);
}
