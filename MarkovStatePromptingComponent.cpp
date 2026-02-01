#include "MarkovStatePromptingComponent.h"

#include "Misc/DateTime.h"

UMarkovStatePromptingComponent::UMarkovStatePromptingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMarkovStatePromptingComponent::BeginPlay()
{
    Super::BeginPlay();

    RandomStream.Initialize(static_cast<int32>(FDateTime::UtcNow().GetTicks() & 0x7fffffff));
}

void UMarkovStatePromptingComponent::AddPrompt(const FString& Category, const FString& Prompt, float Probability, int32 State)
{
    FMarkovPromptEntry Entry;
    Entry.Prompt = Prompt;
    Entry.Probability = Probability;
    Entry.State = State;

    QuantumCache.FindOrAdd(Category).Add(MoveTemp(Entry));
}

FString UMarkovStatePromptingComponent::GetDefaultPrompt(const FString& Category) const
{
    const TArray<FMarkovPromptEntry>* States = QuantumCache.Find(Category);
    if (!States || States->Num() == 0)
    {
        return MissingPromptMessage;
    }

    return SelectByProbability(*States);
}

FString UMarkovStatePromptingComponent::SelectByProbability(const TArray<FMarkovPromptEntry>& States) const
{
    float TotalProbability = 0.0f;
    for (const FMarkovPromptEntry& Entry : States)
    {
        TotalProbability += Entry.Probability;
    }

    if (TotalProbability <= 0.0f)
    {
        return States.Last().Prompt;
    }

    const float RandomValue = RandomStream.FRandRange(0.0f, TotalProbability);
    float Cumulative = 0.0f;

    for (const FMarkovPromptEntry& Entry : States)
    {
        Cumulative += Entry.Probability;
        if (RandomValue <= Cumulative)
        {
            return Entry.Prompt;
        }
    }

    return States.Last().Prompt;
}
