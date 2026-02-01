#include "SeasonalHarmonicIntegrationComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"

USeasonalHarmonicIntegrationComponent::USeasonalHarmonicIntegrationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USeasonalHarmonicIntegrationComponent::BeginPlay()
{
    Super::BeginPlay();
    StartTime = GetWorld()->GetTimeSeconds();
}

void USeasonalHarmonicIntegrationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SimulateHarmonicIntegration();
}

void USeasonalHarmonicIntegrationComponent::SimulateHarmonicIntegration() const
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
    FVector PreviousPoint = FVector::ZeroVector;
    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

    for (int32 Index = 0; Index < TotalPoints; ++Index)
    {
        const float TimeValue = static_cast<float>(Index) / static_cast<float>(Resolution);
        const float Hs = H0 * (1.0f + Gamma * FMath::Sin(OmegaJ * TimeValue + Phi));
        const FVector CurrentPoint = Origin + FVector(TimeValue, Hs, 0.0f);

        if (Index > 0)
        {
            DrawDebugLine(World, PreviousPoint, CurrentPoint, FColor::Red, false, 0.01f);
        }

        PreviousPoint = CurrentPoint;
    }
}
