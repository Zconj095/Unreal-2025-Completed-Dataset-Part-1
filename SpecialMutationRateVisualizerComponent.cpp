#include "SpecialMutationRateVisualizerComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

USpecialMutationRateVisualizerComponent::USpecialMutationRateVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USpecialMutationRateVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!PointActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PointActorClass is not assigned."));
        return;
    }

    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
    const float Step = FMath::Max(TemperatureStep, KINDA_SMALL_NUMBER);

    for (float Temperature = TemperatureStart; Temperature <= TemperatureEnd; Temperature += Step)
    {
        const float Rate = CalculateMutationRate(Lambda, EnergyBarrier, Temperature, MagicalFactor);

        const FVector SpawnLocation = Origin + FVector(Temperature - TemperatureStart, Rate * 50.0f, 0.0f);
        GetWorld()->SpawnActor<AActor>(PointActorClass, SpawnLocation, FRotator::ZeroRotator);

        UE_LOG(LogTemp, Log, TEXT("Temperature: %.2fK, Mutation Rate: %.4f"), Temperature, Rate);
    }
}

float USpecialMutationRateVisualizerComponent::CalculateMutationRate(float LambdaValue, float Barrier, float Temperature, float MagicalBoost) const
{
    if (Temperature <= 0.0f)
    {
        return 0.0f;
    }

    const float Arrhenius = LambdaValue * FMath::Exp(-Barrier / Temperature);
    return Arrhenius * (1.0f + MagicalBoost);
}
