// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIBrainNeuronComponent.generated.h"

/**
 * Lightweight representation of a neuron connection. Extend as needed to mirror your
 * Unity-side AIBrainConnection data.
 */
USTRUCT(BlueprintType)
struct FAIBrainConnection
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Brain|Connection")
    FString ConnectionName = TEXT("Connection");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Brain|Connection")
    float Weight = 1.0f;

    FAIBrainConnection() = default;
    FAIBrainConnection(const FString& InName, float InWeight = 1.0f)
        : ConnectionName(InName)
        , Weight(InWeight)
    {}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAIBrainNeuronComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAIBrainNeuronComponent();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Brain")
    FString AIBrainNeuronType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Brain")
    TArray<FAIBrainConnection> AIBrainConnections;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Brain")
    float State = 0.0f;

    // Equivalent to the Unity method meant to be overridden.
    UFUNCTION(BlueprintNativeEvent, Category="AI Brain")
    void Process();
    virtual void Process_Implementation();

    UFUNCTION(BlueprintCallable, Category="AI Brain")
    void UpdateState(float NewState);
};
