// Converted from Unity MonoBehaviour to an Unreal ActorComponent.
#include "ApertureControlComponent.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

UApertureControlComponent::UApertureControlComponent()
{
#if WITH_EDITOR
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bTickEvenWhenPaused = true;
#endif
}

void UApertureControlComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Verbose, TEXT("ApertureControl initialized: Radius=%.2f, Intensity=%.2f"), ApertureRadius, IntensityFactor);
}

float UApertureControlComponent::CalculateIntensity(float BeamRadius) const
{
    if (BeamRadius > ApertureRadius)
    {
        const float BlockedIntensity = FMath::Max(0.0f, IntensityFactor - (BeamRadius - ApertureRadius));
        return FMath::Clamp(BlockedIntensity, 0.0f, IntensityFactor);
    }

    return IntensityFactor;
}

#if WITH_EDITOR
void UApertureControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetWorld() || !GetOwner())
    {
        return;
    }

    if (GetWorld()->WorldType == EWorldType::Editor || GetWorld()->WorldType == EWorldType::EditorPreview)
    {
        const FVector Center = GetOwner()->GetActorLocation();
        DrawDebugSphere(GetWorld(), Center, ApertureRadius, 32, FColor::Blue, false, -1.0f, 0, 1.0f);
    }
}
#endif
