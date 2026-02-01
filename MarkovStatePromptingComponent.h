#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarkovStatePromptingComponent.generated.h"

USTRUCT(BlueprintType)
struct FMarkovPromptEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Markov Prompting")
    FString Prompt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Markov Prompting")
    float Probability = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Markov Prompting")
    int32 State = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UMarkovStatePromptingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMarkovStatePromptingComponent();

    UFUNCTION(BlueprintCallable, Category = "Markov Prompting")
    void AddPrompt(const FString& Category, const FString& Prompt, float Probability, int32 State);

    UFUNCTION(BlueprintCallable, Category = "Markov Prompting")
    FString GetDefaultPrompt(const FString& Category) const;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Markov Prompting")
    FString MissingPromptMessage = TEXT("No default prompt found");

    TMap<FString, TArray<FMarkovPromptEntry>> QuantumCache;
    mutable FRandomStream RandomStream;

    FString SelectByProbability(const TArray<FMarkovPromptEntry>& States) const;
};
