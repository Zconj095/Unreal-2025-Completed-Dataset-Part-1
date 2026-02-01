// Converted from Unity MonoBehaviour to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeliefNetworkComponent.generated.h"

USTRUCT(BlueprintType)
struct FBeliefLayerSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Belief Network")
    int32 Neurons = 0;
};

USTRUCT()
struct FBeliefLayer
{
    GENERATED_BODY()

    int32 Neurons = 0;
    TArray<float> Values;
    TArray<float> Biases;
    TArray<float> Weights; // Flattened row-major: Neuron x PrevNeurons
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBeliefNetworkComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBeliefNetworkComponent();

    /** Defines the architecture (neurons per layer). The first entry is the input layer. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Belief Network")
    TArray<FBeliefLayerSettings> LayerDefinitions;

    UFUNCTION(BlueprintCallable, Category="Belief Network")
    void InitializeNetwork();

    UFUNCTION(BlueprintCallable, Category="Belief Network")
    bool ForwardPropagation(const TArray<float>& Inputs, TArray<float>& OutOutputs);

    UFUNCTION(BlueprintCallable, Category="Belief Network")
    bool HebbianLearning(float LearningRate = 0.01f);

    UFUNCTION(BlueprintCallable, Category="Belief Network")
    void ApplyEvolution(float MutationRate = 0.1f, float MutationMagnitude = 0.5f);

    UFUNCTION(BlueprintCallable, Category="Belief Network")
    bool QuantumBeliefUpdate(const TArray<float>& StateVector, const TArray<float>& TransitionMatrix, TArray<float>& OutState);

protected:
    virtual void BeginPlay() override;

private:
    TArray<FBeliefLayer> Layers;
    FRandomStream Random;

    void InitializeWeights(FBeliefLayer& Layer, int32 PrevLayerNeurons);
    float ReLU(float Value) const;
    int32 GetWeightIndex(int32 Row, int32 Col, int32 PrevNeurons) const;
};
