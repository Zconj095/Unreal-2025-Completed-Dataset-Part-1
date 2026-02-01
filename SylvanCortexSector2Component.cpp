#include "SylvanCortexSector2Component.h"

#include "Math/UnrealMathUtility.h"

namespace
{
double RandomValue()
{
    return FMath::FRandRange(-1.0f, 1.0f);
}
}

USylvanCortexSector2Component::USylvanCortexSector2Component()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USylvanCortexSector2Component::BeginPlay()
{
    Super::BeginPlay();

    InitializeParameters();

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

void USylvanCortexSector2Component::InitializeParameters()
{
    const int32 WeightCount = OutputSize * InputSize;

    Weights.Init(0.0, WeightCount);
    Inputs.Init(0.0, InputSize);
    Biases.Init(0.0, OutputSize);

    for (int32 Index = 0; Index < WeightCount; ++Index)
    {
        Weights[Index] = RandomValue();
    }

    for (int32 Index = 0; Index < InputSize; ++Index)
    {
        Inputs[Index] = RandomValue();
    }

    for (int32 Index = 0; Index < OutputSize; ++Index)
    {
        Biases[Index] = RandomValue();
    }
}

double USylvanCortexSector2Component::Sigmoid(double Value) const
{
    return 1.0 / (1.0 + FMath::Exp(-Value));
}

void USylvanCortexSector2Component::ComputeSpellVector(TArray<double>& OutVector) const
{
    OutVector.Init(0.0, OutputSize);

    for (int32 OutputIndex = 0; OutputIndex < OutputSize; ++OutputIndex)
    {
        double Sum = Biases[OutputIndex];
        for (int32 InputIndex = 0; InputIndex < InputSize; ++InputIndex)
        {
            Sum += Weights[OutputIndex * InputSize + InputIndex] * Inputs[InputIndex];
        }
        OutVector[OutputIndex] = Sigmoid(Sum);
    }
}
