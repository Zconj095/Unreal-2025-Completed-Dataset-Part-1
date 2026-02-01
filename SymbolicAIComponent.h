// Converted from Unity MonoBehaviour SymbolicAI to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymbolicAIComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymbolicAIComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymbolicAIComponent();

    /** Knowledge base linking concepts to importance scores */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Symbolic AI")
    TMap<FString, float> KnowledgeBase;

    UFUNCTION(BlueprintCallable, Category="Symbolic AI")
    void AddKnowledge(const FString& Concept, float Importance);

    UFUNCTION(BlueprintCallable, Category="Symbolic AI")
    FString Query(const FString& QueryConcept) const;

    UFUNCTION(BlueprintCallable, Category="Symbolic AI")
    void IntegrateNeuralInsights(const FString& Concept, float NeuralWeight);
};
