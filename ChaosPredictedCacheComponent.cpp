#include "ChaosPredictedCacheComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"

UChaosPredictedCacheComponent::UChaosPredictedCacheComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UChaosPredictedCacheComponent::BeginPlay()
{
    Super::BeginPlay();

    if (CleanupInterval > 0.0f && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            CleanupTimerHandle,
            this,
            &UChaosPredictedCacheComponent::CleanupExpiredPrompts,
            CleanupInterval,
            true);
    }
}

void UChaosPredictedCacheComponent::AddPrompt(const FString& Category, const FString& Prompt, float Probability)
{
    if (!GetWorld())
    {
        return;
    }

    const float PredictedExpiry = PredictExpiry(Probability);
    const float ExpiryTime = GetWorld()->GetTimeSeconds() + PredictedExpiry;

    FChaosPromptEntry Entry;
    Entry.Prompt = Prompt;
    Entry.Probability = Probability;
    Entry.ExpiryTime = ExpiryTime;

    QuantumCache.FindOrAdd(Category).Add(MoveTemp(Entry));
}

float UChaosPredictedCacheComponent::PredictExpiry(float Probability) const
{
    return BaseExpiry * (1.0f + Probability * ChaosFactor);
}

void UChaosPredictedCacheComponent::CleanupExpiredPrompts()
{
    if (!GetWorld())
    {
        return;
    }

    const float Now = GetWorld()->GetTimeSeconds();

    for (auto& Pair : QuantumCache)
    {
        Pair.Value.RemoveAll([Now](const FChaosPromptEntry& Entry)
        {
            return Now >= Entry.ExpiryTime;
        });
    }
}
