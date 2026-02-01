#include "QuantumCacheMetadataComponent.h"

#include "Misc/DateTime.h"

UQuantumCacheMetadataComponent::UQuantumCacheMetadataComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuantumCacheMetadataComponent::BeginPlay()
{
    Super::BeginPlay();

    RandomStream.Initialize(static_cast<int32>(FDateTime::UtcNow().GetTicks() & 0x7fffffff));
}

void UQuantumCacheMetadataComponent::StoreMetadata(const FString& Category, const FString& MetadataKey, const FString& MetadataValue, float Probability)
{
    FQuantumMetadataEntry Entry;
    Entry.MetadataKey = MetadataKey;
    Entry.MetadataValue = MetadataValue;
    Entry.Probability = Probability;
    Entry.QuantumState = GenerateQuantumState(Probability);
    Entry.Coherence = CalculateQuantumCoherence(Entry.QuantumState);

    QuantumMetadataCache.FindOrAdd(Category).Add(MoveTemp(Entry));
}

FString UQuantumCacheMetadataComponent::RetrieveMetadata(const FString& Category, const FString& MetadataKey)
{
    TArray<FQuantumMetadataEntry>* Entries = QuantumMetadataCache.Find(Category);
    if (!Entries)
    {
        return MissingMetadataMessage;
    }

    TArray<int32> MatchingIndices;
    for (int32 Index = 0; Index < Entries->Num(); ++Index)
    {
        const FQuantumMetadataEntry& Entry = (*Entries)[Index];
        if (Entry.MetadataKey == MetadataKey && Entry.Coherence > CoherenceThreshold)
        {
            MatchingIndices.Add(Index);
        }
    }

    if (MatchingIndices.Num() == 0)
    {
        return NoValidMetadataMessage;
    }

    const FString SelectedValue = SelectByProbability(MatchingIndices, *Entries);
    ReinforceMetadata(Category, MetadataKey);
    return SelectedValue;
}

int32 UQuantumCacheMetadataComponent::GenerateQuantumState(float Probability)
{
    return static_cast<int32>(RandomStream.FRandRange(0.0f, QuantumMetadataFactor * 100.0f));
}

float UQuantumCacheMetadataComponent::CalculateQuantumCoherence(int32 QuantumState)
{
    return RandomStream.FRandRange(0.0f, QuantumMetadataFactor) / (static_cast<float>(QuantumState) + 1.0f);
}

void UQuantumCacheMetadataComponent::ReinforceMetadata(const FString& Category, const FString& MetadataKey)
{
    TArray<FQuantumMetadataEntry>* Entries = QuantumMetadataCache.Find(Category);
    if (!Entries)
    {
        return;
    }

    for (FQuantumMetadataEntry& Entry : *Entries)
    {
        if (Entry.MetadataKey == MetadataKey)
        {
            Entry.Coherence = CalculateQuantumCoherence(Entry.QuantumState);
            break;
        }
    }
}

FString UQuantumCacheMetadataComponent::SelectByProbability(const TArray<int32>& Indices, const TArray<FQuantumMetadataEntry>& Entries)
{
    float TotalProbability = 0.0f;
    for (int32 Index : Indices)
    {
        TotalProbability += Entries[Index].Probability;
    }

    if (TotalProbability <= 0.0f)
    {
        return Entries[Indices.Last()].MetadataValue;
    }

    const float RandomValue = RandomStream.FRandRange(0.0f, TotalProbability);
    float Cumulative = 0.0f;

    for (int32 Index : Indices)
    {
        Cumulative += Entries[Index].Probability;
        if (RandomValue <= Cumulative)
        {
            return Entries[Index].MetadataValue;
        }
    }

    return Entries[Indices.Last()].MetadataValue;
}
