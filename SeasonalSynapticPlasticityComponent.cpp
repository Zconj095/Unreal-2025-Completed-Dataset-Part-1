#include "SeasonalSynapticPlasticityComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

USeasonalSynapticPlasticityComponent::USeasonalSynapticPlasticityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USeasonalSynapticPlasticityComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USeasonalSynapticPlasticityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SimulateSynapticPlasticity();
}

void USeasonalSynapticPlasticityComponent::SimulateSynapticPlasticity() const
{
    if (Resolution <= 0 || SimulationDuration <= 0.0f)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const int32 TotalPoints = FMath::Max(1, FMath::RoundToInt(Resolution * SimulationDuration));
    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
    FVector PreviousPoint = Origin;

    for (int32 Index = 0; Index <= TotalPoints; ++Index)
    {
        const float TimeValue = Index / static_cast<float>(Resolution);
        const float Sp = S0 * (1.0f + Beta * Tb * FMath::Cos(OmegaJ * TimeValue));
        const FVector CurrentPoint = Origin + FVector(TimeValue, Sp, 0.0f);

        if (Index > 0)
        {
            DrawDebugLine(World, PreviousPoint, CurrentPoint, FColor::Blue, false, 0.01f);
        }

        PreviousPoint = CurrentPoint;
    }
}
