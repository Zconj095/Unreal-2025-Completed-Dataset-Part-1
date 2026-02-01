#include "SeasonalNeuralActivityComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

USeasonalNeuralActivityComponent::USeasonalNeuralActivityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USeasonalNeuralActivityComponent::BeginPlay()
{
    Super::BeginPlay();

    StartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

void USeasonalNeuralActivityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    DrawSeasonalActivityCurve();
}

void USeasonalNeuralActivityComponent::DrawSeasonalActivityCurve() const
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
        const float ActivityValue = N0 * (1.0f + Amplitude * FMath::Cos(OmegaJ * TimeValue + Phi));
        const FVector CurrentPoint = Origin + FVector(TimeValue, ActivityValue, 0.0f);

        if (Step > 0)
        {
            DrawDebugLine(World, PreviousPoint, CurrentPoint, FColor::Cyan, false, 0.01f);
        }

        PreviousPoint = CurrentPoint;
    }
}
