#include "SymbolicParserComponent.h"

#include "Math/UnrealMathUtility.h"

USymbolicParserComponent::USymbolicParserComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Default example weights and transforms
    Weights = { 0.5, 1.0, 1.5 };
    Transformations = { ESymbolicTransformType::Square, ESymbolicTransformType::Sine, ESymbolicTransformType::Logarithm };
}

void USymbolicParserComponent::BeginPlay()
{
    Super::BeginPlay();

    TArray<double> SampleTokens = { 2.0, PI, 1.0 };
    const double Result = ProcessSymbols(SampleTokens);
    UE_LOG(LogTemp, Log, TEXT("Processed Symbol Stream: %.4f"), Result);
}

double USymbolicParserComponent::ProcessSymbols(const TArray<double>& Tokens)
{
    if (Tokens.Num() != Transformations.Num() || Tokens.Num() != Weights.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Token count must match weights/transformation count."));
        return 0.0;
    }

    double Result = 0.0;
    for (int32 Index = 0; Index < Tokens.Num(); ++Index)
    {
        double Input = Tokens[Index];
        double Transformed = ApplyTransformation(Transformations[Index], Input);
        Result += Weights[Index] * Transformed;
    }
    return Result;
}

double USymbolicParserComponent::ApplyTransformation(ESymbolicTransformType Type, double Value)
{
    switch (Type)
    {
        case ESymbolicTransformType::Identity:
            return Value;
        case ESymbolicTransformType::Square:
            return Value * Value;
        case ESymbolicTransformType::Sine:
            return FMath::Sin(Value);
        case ESymbolicTransformType::Logarithm:
            return Value > -1.0 ? FMath::Loge(Value + 1.0) : 0.0;
        default:
            return Value;
    }
}
