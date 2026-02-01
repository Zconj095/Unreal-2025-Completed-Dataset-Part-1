// Converted from Unity MonoBehaviour to Unreal ActorComponent.
#include "BeliefNetworkComponent.h"

#include "Math/UnrealMathUtility.h"
#include "Misc/DateTime.h"

UBeliefNetworkComponent::UBeliefNetworkComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    Random.Initialize(FDateTime::Now().GetTicks());
}

void UBeliefNetworkComponent::BeginPlay()
{
    Super::BeginPlay();

    if (Layers.Num() == 0)
    {
        InitializeNetwork();
    }
}

void UBeliefNetworkComponent::InitializeNetwork()
{
    Layers.Empty();

    if (LayerDefinitions.Num() < 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("BeliefNetworkComponent requires at least 2 layers."));
        return;
    }

    Layers.SetNum(LayerDefinitions.Num());

    for (int32 Index = 0; Index < LayerDefinitions.Num(); ++Index)
    {
        FBeliefLayer& Layer = Layers[Index];
        Layer.Neurons = LayerDefinitions[Index].Neurons;
        Layer.Values.SetNumZeroed(Layer.Neurons);
        Layer.Biases.SetNumZeroed(Layer.Neurons);

        if (Index > 0)
        {
            InitializeWeights(Layer, Layers[Index - 1].Neurons);
        }
    }
}

bool UBeliefNetworkComponent::ForwardPropagation(const TArray<float>& Inputs, TArray<float>& OutOutputs)
{
    if (Layers.Num() < 2 || Inputs.Num() != Layers[0].Neurons)
    {
        return false;
    }

    Layers[0].Values = Inputs;

    for (int32 Index = 1; Index < Layers.Num(); ++Index)
    {
        const FBeliefLayer& PrevLayer = Layers[Index - 1];
        FBeliefLayer& CurrLayer = Layers[Index];

        const int32 PrevNeurons = PrevLayer.Neurons;

        for (int32 NeuronIndex = 0; NeuronIndex < CurrLayer.Neurons; ++NeuronIndex)
        {
            int32 WeightRow = GetWeightIndex(NeuronIndex, 0, PrevNeurons);
            float Sum = CurrLayer.Biases[NeuronIndex];
            for (int32 PrevIndex = 0; PrevIndex < PrevNeurons; ++PrevIndex)
            {
                Sum += PrevLayer.Values[PrevIndex] * CurrLayer.Weights[WeightRow + PrevIndex];
            }
            CurrLayer.Values[NeuronIndex] = ReLU(Sum);
        }
    }

    OutOutputs = Layers.Last().Values;
    return true;
}

bool UBeliefNetworkComponent::HebbianLearning(float LearningRate)
{
    if (Layers.Num() < 2)
    {
        return false;
    }

    for (int32 Index = 1; Index < Layers.Num(); ++Index)
    {
        FBeliefLayer& CurrLayer = Layers[Index];
        const FBeliefLayer& PrevLayer = Layers[Index - 1];
        const int32 PrevNeurons = PrevLayer.Neurons;

        for (int32 NeuronIndex = 0; NeuronIndex < CurrLayer.Neurons; ++NeuronIndex)
        {
            int32 RowStart = GetWeightIndex(NeuronIndex, 0, PrevNeurons);
            for (int32 PrevIndex = 0; PrevIndex < PrevNeurons; ++PrevIndex)
            {
                const float DeltaWeight = LearningRate * PrevLayer.Values[PrevIndex] * CurrLayer.Values[NeuronIndex];
                CurrLayer.Weights[RowStart + PrevIndex] += DeltaWeight;
            }
        }
    }

    return true;
}

void UBeliefNetworkComponent::ApplyEvolution(float MutationRate, float MutationMagnitude)
{
    for (FBeliefLayer& Layer : Layers)
    {
        const int32 WeightCount = Layer.Weights.Num();
        for (int32 Index = 0; Index < WeightCount; ++Index)
        {
            if (Random.FRand() < MutationRate)
            {
                Layer.Weights[Index] += (Random.FRand() * 2.0f - 1.0f) * MutationMagnitude;
            }
        }
    }
}

bool UBeliefNetworkComponent::QuantumBeliefUpdate(const TArray<float>& StateVector, const TArray<float>& TransitionMatrix, TArray<float>& OutState)
{
    const int32 StateSize = StateVector.Num();
    if (StateSize == 0 || TransitionMatrix.Num() != StateSize * StateSize)
    {
        return false;
    }

    OutState.SetNumZeroed(StateSize);

    for (int32 Row = 0; Row < StateSize; ++Row)
    {
        float Sum = 0.0f;
        for (int32 Col = 0; Col < StateSize; ++Col)
        {
            Sum += StateVector[Col] * TransitionMatrix[Row * StateSize + Col];
        }
        OutState[Row] = Sum;
    }

    float Total = 0.0f;
    for (float Value : OutState)
    {
        Total += Value;
    }

    if (Total > SMALL_NUMBER)
    {
        for (float& Value : OutState)
        {
            Value /= Total;
        }
    }

    return true;
}

void UBeliefNetworkComponent::InitializeWeights(FBeliefLayer& Layer, int32 PrevLayerNeurons)
{
    const int32 WeightCount = Layer.Neurons * PrevLayerNeurons;
    Layer.Weights.SetNumUninitialized(WeightCount);

    for (int32 Index = 0; Index < WeightCount; ++Index)
    {
        Layer.Weights[Index] = Random.FRandRange(-1.0f, 1.0f);
    }
}

float UBeliefNetworkComponent::ReLU(float Value) const
{
    return FMath::Max(0.0f, Value);
}

int32 UBeliefNetworkComponent::GetWeightIndex(int32 Row, int32 Col, int32 PrevNeurons) const
{
    return Row * PrevNeurons + Col;
}
