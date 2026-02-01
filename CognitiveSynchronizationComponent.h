// Converted from Unity MonoBehaviour CognitiveSynchronization to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveSynchronizationComponent.generated.h"

USTRUCT(BlueprintType)
struct FCognitiveNeuron
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognition")
    float Phase = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognition")
    float FiringRate = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveSynchronizationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCognitiveSynchronizationComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Synchronization", meta=(ClampMin=1))
    int32 NumberOfNeurons = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Synchronization", meta=(ClampMin=0.0f))
    float CouplingStrength = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Synchronization", meta=(ClampMin=0.0f))
    float LearningRate = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Synchronization", meta=(ClampMin=0.01f))
    float PhaseUpdateInterval = 0.1f;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    TArray<FCognitiveNeuron> Neurons;
    TArray<float> ConnectionWeights;
    FTimerHandle PhaseUpdateHandle;

    void InitializeNeurons();
    void InitializeConnections();
    void UpdateNeuronStates();
    void DebugNeuronStates() const;
    float NormalizePhase(float Phase) const;
    int32 GetWeightIndex(int32 Row, int32 Col) const;
};
