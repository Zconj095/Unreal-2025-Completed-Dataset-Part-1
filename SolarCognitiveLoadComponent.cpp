#include "SolarCognitiveLoadComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

USolarCognitiveLoadComponent::USolarCognitiveLoadComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarCognitiveLoadComponent::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {
        LastUpdateTime = World->GetTimeSeconds();
    }
}

void USolarCognitiveLoadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const float CurrentTime = World->GetTimeSeconds();
    const float DeltaSeconds = FMath::Max(CurrentTime - LastUpdateTime, 0.0f);

    if (DeltaSeconds <= 0.0f)
    {
        LastUpdateTime = CurrentTime;
        return;
    }

    const float Interaction = InteractionFunction(EnvironmentalStimuli, RadiativeStimuli);
    CumulativeSum += Interaction * DeltaSeconds;

    if (!FMath::IsNearlyZero(ProcessingTimeConstant))
    {
        SolarCognitiveLoad = CumulativeSum / ProcessingTimeConstant;
    }
    else
    {
        SolarCognitiveLoad = 0.0f;
        UE_LOG(LogTemp, Warning, TEXT("ProcessingTimeConstant must be non-zero for solar cognitive load calculations."));
    }

    LastUpdateTime = CurrentTime;
    UE_LOG(LogTemp, Log, TEXT("Solar Cognitive Load (Ls): %.2f"), SolarCognitiveLoad);
}

float USolarCognitiveLoadComponent::InteractionFunction(float Es, float Rs) const
{
    return Es + Rs;
}
