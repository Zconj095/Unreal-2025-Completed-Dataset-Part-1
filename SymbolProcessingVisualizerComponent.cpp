#include "SymbolProcessingVisualizerComponent.h"

#include "SymbolicParserComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

USymbolProcessingVisualizerComponent::USymbolProcessingVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USymbolProcessingVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!PointActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PointActorClass is not assigned."));
        return;
    }

    if (Weights.Num() != Transforms.Num() || Weights.Num() != Tokens.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("Tokens, weights, and transformations must have the same length."));
        return;
    }

    double Sum = 0.0;
    for (int32 Index = 0; Index < Tokens.Num(); ++Index)
    {
        double Transformed = ApplyTransform(Transforms[Index], Tokens[Index]);
        Sum += Weights[Index] * Transformed;
    }
    const double Value = Sum;
    SpawnPoint(Value);
}

void USymbolProcessingVisualizerComponent::SpawnPoint(double Value) const
{
    if (!PointActorClass)
    {
        return;
    }

    if (!GetWorld())
    {
        return;
    }

    const FVector Location = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
    AActor* PointActor = GetWorld()->SpawnActor<AActor>(PointActorClass, Location, FRotator::ZeroRotator);
    if (!PointActor)
    {
        return;
    }

    const float Scale = FMath::Max(0.1f, static_cast<float>(Value));
    PointActor->SetActorScale3D(FVector(1.0f, Scale, 1.0f));
}

double USymbolProcessingVisualizerComponent::ApplyTransform(ESymbolicTransformType Type, double Value)
{
    switch (Type)
    {
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
