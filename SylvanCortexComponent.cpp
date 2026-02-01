#include "SylvanCortexComponent.h"

#include "Math/UnrealMathUtility.h"

namespace
{
double RandWeight()
{
    return FMath::FRandRange(-1.0f, 1.0f);
}
}

USylvanCortexComponent::USylvanCortexComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USylvanCortexComponent::BeginPlay()
{
    Super::BeginPlay();
    InitializeNetwork();

    TArray<double> SpellVector;
    ComputeSpellVector(SpellVector);

    FString Output = TEXT("[");
    for (int32 Index = 0; Index < SpellVector.Num(); ++Index)
    {
        Output += FString::SanitizeFloat(SpellVector[Index]);
        if (Index < SpellVector.Num() - 1)
        {
            Output += TEXT(", ");
        }
    }
    Output += TEXT("]");
    UE_LOG(LogTemp, Log, TEXT("M_spell: %s"), *Output);
}

void USylvanCortexComponent::InitializeNetwork()
{
    const int32 WeightCount = OutputSize * InputSize;
    Weights.Init(0.0, WeightCount);
    Bias.Init(0.0, OutputSize);

    for (int32 Index = 0; Index < WeightCount; ++Index)
    {
        Weights[Index] = RandWeight();
    }

    for (int32 Index = 0; Index < OutputSize; ++Index)
    {
        Bias[Index] = RandWeight();
    }
}

double USylvanCortexComponent::Sigmoid(double Value) const
{
    return 1.0 / (1.0 + FMath::Exp(-Value));
}

void USylvanCortexComponent::ComputeSpellVector(TArray<double>& OutVector) const
{
    OutVector.Init(0.0, OutputSize);

    TArray<double> InputVector;
    InputVector.Init(0.0, InputSize);
    for (int32 Index = 0; Index < InputSize; ++Index)
    {
        InputVector[Index] = RandWeight();
    }

    for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
    {
        double Sum = Bias[OutputIndex];
        for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
        {
            Sum += Weights[OutputIndex * InputSize + InputIndex] * InputVector[InputIndex];
        }
        OutVector[OutputIndex] = Sigmoid(Sum);
    }
}
