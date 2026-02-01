#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChaosPredictedCacheComponent.generated.h"

USTRUCT(BlueprintType)
struct FChaosPromptEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos Cache")
    FString Prompt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos Cache")
    float Probability = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chaos Cache")
    float ExpiryTime = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UChaosPredictedCacheComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UChaosPredictedCacheComponent();

    UFUNCTION(BlueprintCallable, Category = "Chaos Cache")
    void AddPrompt(const FString& Category, const FString& Prompt, float Probability);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Chaos Cache")
    float BaseExpiry = 30.0f;

    UPROPERTY(EditAnywhere, Category = "Chaos Cache")
    float ChaosFactor = 1.2f;

    UPROPERTY(EditAnywhere, Category = "Chaos Cache")
    float CleanupInterval = 5.0f;

    TMap<FString, TArray<FChaosPromptEntry>> QuantumCache;
    FTimerHandle CleanupTimerHandle;

    float PredictExpiry(float Probability) const;
    void CleanupExpiredPrompts();
};
