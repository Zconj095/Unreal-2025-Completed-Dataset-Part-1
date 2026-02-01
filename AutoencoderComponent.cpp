// Converted from Unity MonoBehaviour Autoencoder to Unreal ActorComponent.
#include "AutoencoderComponent.h"

#include "Math/UnrealMathUtility.h"

UAutoencoderComponent::UAutoencoderComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAutoencoderComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeTrainingData();
    InitializeWeights();
    PerformTraining();

    const float FinalFitness = EvaluateFitness();
    UE_LOG(LogTemp, Log, TEXT("Autoencoder training complete. Final fitness: %.6f"), FinalFitness);
}

void UAutoencoderComponent::InitializeTrainingData()
{
    TrainingData.Empty();

    TrainingData.Add({0.1f, 0.2f, 0.3f, 0.4f, 0.5f});
    TrainingData.Add({0.5f, 0.4f, 0.3f, 0.2f, 0.1f});
    TrainingData.Add({0.3f, 0.7f, 0.8f, 0.1f, 0.4f});
}

void UAutoencoderComponent::InitializeWeights()
{
    const int32 InputHiddenCount = InputSize * HiddenSize;
    WeightsInputToHidden.SetNumUninitialized(InputHiddenCount);
    for (int32 Index = 0; Index < InputHiddenCount; ++Index)
    {
        WeightsInputToHidden[Index] = FMath::FRandRange(0.0f, 0.1f);
    }

    const int32 HiddenOutputCount = HiddenSize * OutputSize;
    WeightsHiddenToOutput.SetNumUninitialized(HiddenOutputCount);
    for (int32 Index = 0; Index < HiddenOutputCount; ++Index)
    {
        WeightsHiddenToOutput[Index] = FMath::FRandRange(0.0f, 0.1f);
    }

    BiasesHidden.Init(0.0f, HiddenSize);
    BiasesOutput.Init(0.0f, OutputSize);
    for (int32 Index = 0; Index < HiddenSize; ++Index)
    {
        BiasesHidden[Index] = FMath::FRandRange(0.0f, 0.1f);
    }
    for (int32 Index = 0; Index < OutputSize; ++Index)
    {
        BiasesOutput[Index] = FMath::FRandRange(0.0f, 0.1f);
    }
}

void UAutoencoderComponent::PerformTraining()
{
    if (TrainingData.Num() == 0)
    {
        return;
    }

    for (int32 Epoch = 0; Epoch < Epochs; ++Epoch)
    {
        for (const TArray<float>& Sample : TrainingData)
        {
            SingleTrainingStep(Sample);
        }

        if (Epoch % 100 == 0)
        {
            const float Fitness = EvaluateFitness();
            UE_LOG(LogTemp, Log, TEXT("Epoch %d, Fitness: %.6f"), Epoch, Fitness);
        }
    }
}

void UAutoencoderComponent::SingleTrainingStep(const TArray<float>& InputSample)
{
    if (InputSample.Num() != InputSize)
    {
        return;
    }

    TArray<float> Hidden;
    Hidden.SetNumZeroed(HiddenSize);
    TArray<float> Output;
    Output.SetNumZeroed(OutputSize);

    ComputeForward(InputSample, Hidden, Output);

    TArray<float> OutputError;
    OutputError.SetNumZeroed(OutputSize);
    for (int32 Index = 0; Index < OutputSize; ++Index)
    {
        OutputError[Index] = InputSample[Index] - Output[Index];
    }

    TArray<float> HiddenError;
    HiddenError.SetNumZeroed(HiddenSize);
    for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
    {
        float Error = 0.0f;
        for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
        {
            const int32 WeightIndex = HiddenIndex * OutputSize + OutputIndex;
            Error += OutputError[OutputIndex] * WeightsHiddenToOutput[WeightIndex];
        }
        HiddenError[HiddenIndex] = Error * ActivateDerivative(Hidden[HiddenIndex]);
    }

    for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
    {
        for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
        {
            const int32 WeightIndex = HiddenIndex * OutputSize + OutputIndex;
            WeightsHiddenToOutput[WeightIndex] += LearningRate * OutputError[OutputIndex] * Hidden[HiddenIndex];
        }
    }

    for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
    {
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
        {
            const int32 WeightIndex = InputIndex * HiddenSize + HiddenIndex;
            WeightsInputToHidden[WeightIndex] += LearningRate * HiddenError[HiddenIndex] * InputSample[InputIndex];
        }
    }

    for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
    {
        BiasesHidden[HiddenIndex] += LearningRate * HiddenError[HiddenIndex];
    }

    for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
    {
        BiasesOutput[OutputIndex] += LearningRate * OutputError[OutputIndex];
    }
}

void UAutoencoderComponent::ComputeForward(const TArray<float>& InputSample, TArray<float>& Hidden, TArray<float>& Output) const
{
    for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
    {
        float Value = BiasesHidden[HiddenIndex];
        for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
        {
            const int32 WeightIndex = InputIndex * HiddenSize + HiddenIndex;
            Value += InputSample[InputIndex] * WeightsInputToHidden[WeightIndex];
        }
        Hidden[HiddenIndex] = ApplyActivation(Value);
    }

    for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
    {
        float Value = BiasesOutput[OutputIndex];
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenSize; ++HiddenIndex)
        {
            const int32 WeightIndex = HiddenIndex * OutputSize + OutputIndex;
            Value += Hidden[HiddenIndex] * WeightsHiddenToOutput[WeightIndex];
        }
        Output[OutputIndex] = ApplyActivation(Value);
    }
}

float UAutoencoderComponent::ApplyActivation(float Value) const
{
    return FMath::Max(0.0f, Value);
}

float UAutoencoderComponent::ActivateDerivative(float Value) const
{
    return Value > 0.0f ? 1.0f : 0.0f;
}

float UAutoencoderComponent::EvaluateFitness() const
{
    if (TrainingData.Num() == 0)
    {
        return 0.0f;
    }

    TArray<float> Hidden;
    Hidden.SetNumZeroed(HiddenSize);
    TArray<float> Output;
    Output.SetNumZeroed(OutputSize);

    float TotalError = 0.0f;
    for (const TArray<float>& Sample : TrainingData)
    {
        if (Sample.Num() != InputSize)
        {
            continue;
        }

        ComputeForward(Sample, Hidden, Output);
        for (int32 Index = 0; Index < InputSize; ++Index)
        {
            TotalError += FMath::Abs(Sample[Index] - Output[Index]);
        }
    }

    return -TotalError;
}
