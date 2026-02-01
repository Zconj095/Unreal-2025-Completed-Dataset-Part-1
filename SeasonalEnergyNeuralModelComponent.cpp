#include "SeasonalEnergyNeuralModelComponent.h"

#include "Math/UnrealMathUtility.h"

#include <cmath>

USeasonalEnergyNeuralModelComponent::USeasonalEnergyNeuralModelComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    InitializeNetwork();
}

void USeasonalEnergyNeuralModelComponent::InitializeNetwork()
{
    for (int32 Index = 0; Index < HiddenLayerNeuronCount; ++Index)
    {
        HiddenWeights[Index] = FMath::FRandRange(-1.0, 1.0);
        HiddenBias[Index] = FMath::FRandRange(-1.0, 1.0);
        OutputWeights[Index] = FMath::FRandRange(-1.0, 1.0);
    }

    OutputBias = FMath::FRandRange(-1.0, 1.0);
}

double USeasonalEnergyNeuralModelComponent::Predict(double Time) const
{
    double HiddenOutputs[HiddenLayerNeuronCount];

    for (int32 Index = 0; Index < HiddenLayerNeuronCount; ++Index)
    {
        double HiddenSum = HiddenBias[Index] + HiddenWeights[Index] * Time;
        HiddenOutputs[Index] = Sigmoid(HiddenSum);
    }

    double OutputSum = OutputBias;
    for (int32 Index = 0; Index < HiddenLayerNeuronCount; ++Index)
    {
        OutputSum += OutputWeights[Index] * HiddenOutputs[Index];
    }

    return OutputSum;
}

double USeasonalEnergyNeuralModelComponent::Sigmoid(double Value) const
{
    return 1.0 / (1.0 + static_cast<double>(FMath::Exp(static_cast<float>(-Value))));
}

void USeasonalEnergyNeuralModelComponent::BeginPlay()
{
    Super::BeginPlay();

    const double TimeValue = 100.0;
    const double PredictedEnergy = Predict(TimeValue);

    UE_LOG(LogTemp, Log, TEXT("Predicted seasonal energy at time t=%.1f: %.6f"), TimeValue, PredictedEnergy);
}
