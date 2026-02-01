// Converted from Unity MonoBehaviour to Unreal Actor Component.
#include "AdvancedOptimizerComponent.h"

#include "Math/UnrealMathUtility.h"

UAdvancedOptimizerComponent::UAdvancedOptimizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAdvancedOptimizerComponent::BeginPlay()
{
    Super::BeginPlay();

    Weights.SetNumZeroed(NumWeights);
    Velocity.SetNumZeroed(NumWeights);
    AccumulatedSquaredGradients.SetNumZeroed(NumWeights);

    InitializeWeights();
    PerformOptimization();

    TArray<FString> FinalWeights;
    FinalWeights.Reserve(Weights.Num());
    for (float Value : Weights)
    {
        FinalWeights.Add(FString::SanitizeFloat(Value));
    }
    UE_LOG(LogTemp, Log, TEXT("Final Weights: %s"), *FString::Join(FinalWeights, TEXT(", ")));
}

void UAdvancedOptimizerComponent::InitializeWeights()
{
    for (float& Weight : Weights)
    {
        Weight = FMath::FRandRange(-1.0f, 1.0f);
    }
}

TArray<float> UAdvancedOptimizerComponent::ComputeGradients() const
{
    TArray<float> Gradients;
    Gradients.SetNumUninitialized(Weights.Num());
    for (int32 Index = 0; Index < Weights.Num(); ++Index)
    {
        Gradients[Index] = 2.0f * Weights[Index];
    }
    return Gradients;
}

void UAdvancedOptimizerComponent::PerformOptimization()
{
    constexpr float Epsilon = 1e-8f;

    for (int32 Epoch = 0; Epoch < Epochs; ++Epoch)
    {
        TArray<float> Gradients = ComputeGradients();

        for (int32 Index = 0; Index < Weights.Num(); ++Index)
        {
            const float GradSquared = FMath::Square(Gradients[Index]);
            AccumulatedSquaredGradients[Index] =
                Rho * AccumulatedSquaredGradients[Index] + (1.0f - Rho) * GradSquared;

            const float GradientScale = Alpha / FMath::Sqrt(AccumulatedSquaredGradients[Index] + Epsilon);
            Velocity[Index] =
                Beta * Velocity[Index] - GradientScale * Gradients[Index];

            Weights[Index] += Velocity[Index];
        }

        LogWeights(Epoch + 1);
    }
}

void UAdvancedOptimizerComponent::LogWeights(int32 Epoch) const
{
    TArray<FString> WeightStrings;
    WeightStrings.Reserve(Weights.Num());
    for (float Value : Weights)
    {
        WeightStrings.Add(FString::SanitizeFloat(Value));
    }

    UE_LOG(LogTemp, Log, TEXT("Epoch %d: Weights = %s"), Epoch, *FString::Join(WeightStrings, TEXT(", ")));
}
