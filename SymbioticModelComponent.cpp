#include "SymbioticModelComponent.h"

#include "Math/UnrealMathUtility.h"

USymbioticModelComponent::USymbioticModelComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USymbioticModelComponent::BeginPlay()
{
    Super::BeginPlay();
    EvaluateBenefit();
}

void USymbioticModelComponent::EvaluateBenefit() const
{
    if (EfficiencyConstant <= 0.0f || ResourceA <= 0.0f || ResourceB <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("All parameters must be greater than zero."));
        return;
    }

    const double Benefit = EfficiencyConstant * ResourceA * ResourceB;
    UE_LOG(LogTemp, Log, TEXT("Total Symbiotic Benefit: %.2f"), Benefit);
}
