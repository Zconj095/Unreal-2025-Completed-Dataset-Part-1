#include "SpecialMagicalEnergyPredictorComponent.h"

#include "Math/UnrealMathUtility.h"

namespace
{
double RandomWeight()
{
    return FMath::FRandRange(-0.5f, 0.5f);
}
}

USpecialMagicalEnergyPredictorComponent::USpecialMagicalEnergyPredictorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USpecialMagicalEnergyPredictorComponent::BeginPlay()
{
    Super::BeginPlay();
    InitializeNetwork();
}

void USpecialMagicalEnergyPredictorComponent::InitializeNetwork()
{
    InputToHiddenWeights.Init(0.0, HiddenSize * InputSize);
    HiddenBias.Init(0.0, HiddenSize);
    HiddenToOutputWeights.Init(0.0, OutputSize * HiddenSize);
    OutputBias.Init(0.0, OutputSize);
    HiddenLayerValues.Init(0.0, HiddenSize);

    for (double& Value : InputToHiddenWeights)
    {
        Value = RandomWeight();
    }

    for (double& Value : HiddenBias)
    {
        Value = RandomWeight();
    }

    for (double& Value : HiddenToOutputWeights)
    {
        Value = RandomWeight();
    }

    for (double& Value : OutputBias)
    {
        Value = RandomWeight();
    }
}

double USpecialMagicalEnergyPredictorComponent::Sigmoid(double Value) const
{
    return 1.0 / (1.0 + FMath::Exp(-Value));
}

void USpecialMagicalEnergyPredictorComponent::Forward(const TArray<double>& Inputs, TArray<double>& OutOutputs) const
{
    HiddenLayerValues.Init(0.0, HiddenSize);

    for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
    {
        double Sum = HiddenBias[HiddenIndex];
        for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
        {
            Sum += InputToHiddenWeights[HiddenIndex * InputSize + InputIndex] * Inputs[InputIndex];
        }
        HiddenLayerValues[HiddenIndex] = Sigmoid(Sum);
    }

    OutOutputs.Init(0.0, OutputSize);
    for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
    {
        double Sum = OutputBias[OutputIndex];
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
        {
            Sum += HiddenToOutputWeights[OutputIndex * HiddenSize + HiddenIndex] * HiddenLayerValues[HiddenIndex];
        }
        OutOutputs[OutputIndex] = Sum;
    }
}

TArray<double> USpecialMagicalEnergyPredictorComponent::Predict(const TArray<double>& Inputs) const
{
    TArray<double> Outputs;
    if (Inputs.Num() != InputSize)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input size mismatch."));
        return Outputs;
    }

    Forward(Inputs, Outputs);
    return Outputs;
}

void USpecialMagicalEnergyPredictorComponent::Train(const TArray<FDoubleArrayWrapper>& Inputs, const TArray<FDoubleArrayWrapper>& Targets, int32 Epochs, double LearningRate)
{
    if (Inputs.Num() != Targets.Num() || Inputs.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Training data mismatch."));
        return;
    }

    for (int32 Epoch = 0; Epoch < Epochs; ++Epoch)
    {
        double TotalError = 0.0;
        for (int32 SampleIndex = 0; SampleIndex < Inputs.Num(); ++SampleIndex)
        {
            const TArray<double>& SampleInput = Inputs[SampleIndex].Values;
            const TArray<double>& SampleTarget = Targets[SampleIndex].Values;

            if (SampleInput.Num() != InputSize || SampleTarget.Num() != OutputSize)
            {
                continue;
            }

            TArray<double> Outputs;
            Forward(SampleInput, Outputs);

            TArray<double> OutputErrors;
            OutputErrors.Init(0.0, OutputSize);
            for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
            {
                const double Error = SampleTarget[OutputIndex] - Outputs[OutputIndex];
                OutputErrors[OutputIndex] = Error;
                TotalError += FMath::Abs(Error);
            }

            TArray<double> HiddenErrors;
            HiddenErrors.Init(0.0, HiddenSize);
            for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
            {
                double Error = 0.0;
                for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
                {
                    Error += HiddenToOutputWeights[OutputIndex * HiddenSize + HiddenIndex] * OutputErrors[OutputIndex];
                }
                HiddenErrors[HiddenIndex] = Error * HiddenLayerValues[HiddenIndex] * (1.0 - HiddenLayerValues[HiddenIndex]);
            }

            for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
            {
                OutputBias[OutputIndex] += LearningRate * OutputErrors[OutputIndex];
                for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
                {
                    HiddenToOutputWeights[OutputIndex * HiddenSize + HiddenIndex] += LearningRate * OutputErrors[OutputIndex] * HiddenLayerValues[HiddenIndex];
                }
            }

            for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
            {
                HiddenBias[HiddenIndex] += LearningRate * HiddenErrors[HiddenIndex];
                for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
                {
                    InputToHiddenWeights[HiddenIndex * InputSize + InputIndex] += LearningRate * HiddenErrors[HiddenIndex] * SampleInput[InputIndex];
                }
            }
        }

        if ((Epoch + 1) % 100 == 0)
        {
            UE_LOG(LogTemp, Log, TEXT("Epoch %d/%d, Avg Error: %.4f"), Epoch + 1, Epochs, TotalError / Inputs.Num());
        }
    }
}
