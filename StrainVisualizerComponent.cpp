#include "StrainVisualizerComponent.h"

#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

UStrainVisualizerComponent::UStrainVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStrainVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();
    ApplyStrain();
}

void UStrainVisualizerComponent::ApplyStrain()
{
    if (!MaterialObject)
    {
        UE_LOG(LogTemp, Warning, TEXT("MaterialObject is not assigned."));
        return;
    }

    const float StrainValue = CalculateStrain(Stress, YoungsModulus);
    USceneComponent* RootComp = MaterialObject->GetRootComponent();
    if (!RootComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("MaterialObject has no root component."));
        return;
    }

    FVector NewScale = RootComp->GetComponentScale();
    NewScale.Y += StrainValue;
    RootComp->SetWorldScale3D(NewScale);

    UE_LOG(LogTemp, Log, TEXT("Strain: %.4f"), StrainValue);
}

float UStrainVisualizerComponent::CalculateStrain(float StressValue, float Youngs) const
{
    if (FMath::IsNearlyZero(Youngs))
    {
        return 0.0f;
    }
    return StressValue / Youngs;
}
