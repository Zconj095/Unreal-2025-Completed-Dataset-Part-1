#include "SolarMemoryRetentionComponent.h"

#include "Math/UnrealMathUtility.h"

USolarMemoryRetentionComponent::USolarMemoryRetentionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarMemoryRetentionComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeElapsed = 0.0f;
}

void USolarMemoryRetentionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimeElapsed += DeltaTime;
    const float MemoryRetention = CalculateMemoryRetention(TimeElapsed);
    UE_LOG(LogTemp, Log, TEXT("Time: %.2fs, Memory Retention (M_s): %.4f"), TimeElapsed, MemoryRetention);
}

float USolarMemoryRetentionComponent::CalculateMemoryRetention(float Time) const
{
    const float NaturalDecay = InitialCapacity * FMath::Exp(-DecayRate * Time);
    const float SolarContribution = SolarBoost * FMath::Exp(-Sensitivity * FMath::Square(Time - PeakTime));
    return NaturalDecay + SolarContribution;
}
