#include "SeasonalMemoryModelComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

USeasonalMemoryModelComponent::USeasonalMemoryModelComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USeasonalMemoryModelComponent::BeginPlay()
{
    Super::BeginPlay();
    StartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

void USeasonalMemoryModelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    DrawMemoryCurve();
}

float USeasonalMemoryModelComponent::ComputeMemory(float Time) const
{
    const float DecayTerm = M0 * FMath::Exp(-Lambda * Time);
    const float PeakTerm = DeltaM * FMath::Exp(-Alpha * FMath::Square(Time - PeakTime));
    return DecayTerm + PeakTerm;
}

void USeasonalMemoryModelComponent::DrawMemoryCurve() const
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

    const int32 TotalSteps = FMath::Max(1, FMath::RoundToInt(Resolution * SimulationDuration));
    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
    FVector PreviousPoint = Origin;

    for (int32 Step = 0; Step <= TotalSteps; ++Step)
    {
        const float TimeValue = Step / static_cast<float>(Resolution);
        const float MemoryValue = ComputeMemory(TimeValue);
        const FVector CurrentPoint = Origin + FVector(TimeValue, MemoryValue, 0.0f);

        if (Step > 0)
        {
            DrawDebugLine(World, PreviousPoint, CurrentPoint, FColor::Magenta, false, 0.01f);
        }

        PreviousPoint = CurrentPoint;
    }
}
