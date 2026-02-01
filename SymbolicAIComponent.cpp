// Converted from Unity MonoBehaviour SymbolicAI to Unreal ActorComponent.
#include "SymbolicAIComponent.h"

USymbolicAIComponent::USymbolicAIComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USymbolicAIComponent::AddKnowledge(const FString& Concept, float Importance)
{
    if (Concept.IsEmpty())
    {
        return;
    }

    KnowledgeBase.FindOrAdd(Concept) += Importance;
}

FString USymbolicAIComponent::Query(const FString& QueryConcept) const
{
    const float* Importance = KnowledgeBase.Find(QueryConcept);
    if (Importance)
    {
        return FString::Printf(TEXT("Concept %s: Importance %.3f"), *QueryConcept, *Importance);
    }

    return FString::Printf(TEXT("Concept %s not found."), *QueryConcept);
}

void USymbolicAIComponent::IntegrateNeuralInsights(const FString& Concept, float NeuralWeight)
{
    AddKnowledge(Concept, NeuralWeight);
}
