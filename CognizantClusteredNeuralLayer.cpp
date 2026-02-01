// Lightweight neural layer utility ported from the Unity version.
#include "CognizantClusteredNeuralLayer.h"

#include "Math/UnrealMathUtility.h"

FCognizantClusteredNeuralLayer::FCognizantClusteredNeuralLayer(int32 InInputSize, int32 InOutputSize, float InLearningRate)
    : InputSize(FMath::Max(1, InInputSize))
    , OutputSize(FMath::Max(1, InOutputSize))
    , LearningRate(FMath::Max(0.0f, InLearningRate))
{
    Weights.SetNumZeroed(InputSize * OutputSize);
    Biases.SetNumZeroed(OutputSize);
    Outputs.SetNumZeroed(OutputSize);
    InitializeWeights();
}

const TArray<float>& FCognizantClusteredNeuralLayer::Forward(const TArray<float>& Inputs)
{
    if (Inputs.Num() != InputSize)
    {
        return Outputs;
    }

    for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
    {
        float Sum = Biases[OutputIndex];
        for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
        {
            const int32 WeightIndex = GetWeightIndex(InputIndex, OutputIndex);
            Sum += Inputs[InputIndex] * Weights[WeightIndex];
        }
        Outputs[OutputIndex] = Sigmoid(Sum);
    }

    return Outputs;
}

TArray<float> FCognizantClusteredNeuralLayer::Backward(const TArray<float>& Inputs, const TArray<float>& OutputErrors)
{
    TArray<float> InputErrors;
    InputErrors.Init(0.0f, InputSize);

    if (Inputs.Num() != InputSize || OutputErrors.Num() != OutputSize)
    {
        return InputErrors;
    }

    for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
    {
        float ErrorSum = 0.0f;
        for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
        {
            const int32 WeightIndex = GetWeightIndex(InputIndex, OutputIndex);
            const float ErrorGradient = OutputErrors[OutputIndex] * SigmoidDerivative(Outputs[OutputIndex]);
            ErrorSum += ErrorGradient * Weights[WeightIndex];
            Weights[WeightIndex] -= LearningRate * ErrorGradient * Inputs[InputIndex];
            Biases[OutputIndex] -= LearningRate * ErrorGradient;
        }
        InputErrors[InputIndex] = ErrorSum;
    }

    return InputErrors;
}

void FCognizantClusteredNeuralLayer::InitializeWeights()
{
    for (int32 Index = 0; Index < Weights.Num(); ++Index)
    {
        Weights[Index] = FMath::FRandRange(-0.5f, 0.5f);
    }

    for (int32 Index = 0; Index < Biases.Num(); ++Index)
    {
        Biases[Index] = FMath::FRandRange(-0.5f, 0.5f);
    }
}

int32 FCognizantClusteredNeuralLayer::GetWeightIndex(int32 InputIndex, int32 OutputIndex) const
{
    return InputIndex * OutputSize + OutputIndex;
}

float FCognizantClusteredNeuralLayer::Sigmoid(float Value)
{
    return 1.0f / (1.0f + FMath::Exp(-Value));
}

float FCognizantClusteredNeuralLayer::SigmoidDerivative(float Value)
{
    return Value * (1.0f - Value);
}
