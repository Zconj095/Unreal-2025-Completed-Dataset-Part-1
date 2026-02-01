// Lightweight neural layer utility ported from the Unity version.
#pragma once

#include "CoreMinimal.h"

class FCognizantClusteredNeuralLayer
{
public:
    FCognizantClusteredNeuralLayer(int32 InInputSize, int32 InOutputSize, float InLearningRate);

    /** Runs a forward pass and returns the output activation array. */
    const TArray<float>& Forward(const TArray<float>& Inputs);

    /**
     * Performs the backward pass, adjusts weights/biases, and returns the input error vector.
     * InputErrors.Num() == Inputs.Num()
     */
    TArray<float> Backward(const TArray<float>& Inputs, const TArray<float>& OutputErrors);

private:
    int32 InputSize = 0;
    int32 OutputSize = 0;
    float LearningRate = 0.1f;

    TArray<float> Weights;  // Row-major: [InputIndex * OutputSize + OutputIndex]
    TArray<float> Biases;
    TArray<float> Outputs;

    void InitializeWeights();
    int32 GetWeightIndex(int32 InputIndex, int32 OutputIndex) const;
    static float Sigmoid(float Value);
    static float SigmoidDerivative(float Value);
};
