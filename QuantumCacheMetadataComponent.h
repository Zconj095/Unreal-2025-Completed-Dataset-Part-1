#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuantumCacheMetadataComponent.generated.h"

USTRUCT(BlueprintType)
struct FQuantumMetadataEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum Metadata")
    FString MetadataKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum Metadata")
    FString MetadataValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum Metadata")
    float Probability = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum Metadata")
    int32 QuantumState = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum Metadata")
    float Coherence = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UQuantumCacheMetadataComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuantumCacheMetadataComponent();

    UFUNCTION(BlueprintCallable, Category = "Quantum Metadata")
    void StoreMetadata(const FString& Category, const FString& MetadataKey, const FString& MetadataValue, float Probability);

    UFUNCTION(BlueprintCallable, Category = "Quantum Metadata")
    FString RetrieveMetadata(const FString& Category, const FString& MetadataKey);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Quantum Metadata")
    float QuantumMetadataFactor = 1.4f;

    UPROPERTY(EditAnywhere, Category = "Quantum Metadata")
    float CoherenceThreshold = 0.7f;

    UPROPERTY(EditAnywhere, Category = "Quantum Metadata")
    FString MissingMetadataMessage = TEXT("No metadata found");

    UPROPERTY(EditAnywhere, Category = "Quantum Metadata")
    FString NoValidMetadataMessage = TEXT("No valid metadata available");

    TMap<FString, TArray<FQuantumMetadataEntry>> QuantumMetadataCache;
    FRandomStream RandomStream;

    int32 GenerateQuantumState(float Probability);
    float CalculateQuantumCoherence(int32 QuantumState);
    void ReinforceMetadata(const FString& Category, const FString& MetadataKey);
    FString SelectByProbability(const TArray<int32>& Indices, const TArray<FQuantumMetadataEntry>& Entries);
};
