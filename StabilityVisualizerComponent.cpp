#include "StabilityVisualizerComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

UStabilityVisualizerComponent::UStabilityVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStabilityVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    TArray<FVector> Wave;
    GenerateWaveFunction(Wave);

    TArray<FVector> Gradients;
    ComputeGradients(Wave, Gradients);

    const double StabilityIndex = ComputeStabilityIndex(Gradients);
    UE_LOG(LogTemp, Log, TEXT("Temporal Stability Index (S): %.4f"), StabilityIndex);

    VisualizeGradients(Gradients);
}

void UStabilityVisualizerComponent::GenerateWaveFunction(TArray<FVector>& OutWave) const
{
    OutWave.SetNum(GridSize);
    for (int32 Index = 0; Index < GridSize; ++Index)
    {
        const float X = Index * Dx;
        OutWave[Index] = FVector(FMath::Sin(X) * AmplitudeScale, FMath::Cos(X) * AmplitudeScale, 0.0f);
    }
}

void UStabilityVisualizerComponent::ComputeGradients(const TArray<FVector>& Wave, TArray<FVector>& OutGradients) const
{
    OutGradients.SetNum(GridSize);
    if (GridSize < 2)
    {
        return;
    }

    for (int32 Index = 0; Index < GridSize - 1; ++Index)
    {
        OutGradients[Index] = (Wave[Index + 1] - Wave[Index]) / Dx;
    }

    OutGradients[GridSize - 1] = FVector::ZeroVector;
}

double UStabilityVisualizerComponent::ComputeStabilityIndex(const TArray<FVector>& Gradients) const
{
    double Sum = 0.0;
    for (const FVector& Gradient : Gradients)
    {
        Sum += Gradient.SizeSquared();
    }

    return Sum * VolumeScaling;
}

void UStabilityVisualizerComponent::VisualizeGradients(const TArray<FVector>& Gradients) const
{
    if (!GradientActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("GradientActorClass is not assigned."));
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

    for (int32 Index = 0; Index < Gradients.Num(); ++Index)
    {
        const FVector& Gradient = Gradients[Index];
        if (Gradient.IsNearlyZero())
        {
            continue;
        }

        FVector SpawnLocation = Origin + FVector(Index * Dx, 0.0f, 0.0f);
        FTransform Transform(FRotator::ZeroRotator, SpawnLocation, FVector(FMath::Max(0.1f, Gradient.X), FMath::Max(0.1f, Gradient.Y), FMath::Max(0.1f, Gradient.Z)));
        World->SpawnActor<AActor>(GradientActorClass, Transform);
    }
}
