#include "SymmetryVisualizerComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

USymmetryVisualizerComponent::USymmetryVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USymmetryVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!PointActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PointActorClass is not assigned."));
        return;
    }

    const FVector NormalizedAxis = Axis.GetSafeNormal();
    const float AngleRadians = FMath::DegreesToRadians(AngleDegrees);

    const FQuat RotationQuat = FQuat(NormalizedAxis, AngleRadians);
    const FVector TransformedPosition = RotationQuat.RotateVector(Position);

    SpawnPoint(Position);
    SpawnPoint(TransformedPosition);
}

void USymmetryVisualizerComponent::SpawnPoint(const FVector& Location) const
{
    if (!GetWorld())
    {
        return;
    }

    const FVector SpawnLocation = (GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector) + Location;
    FTransform Transform(FRotator::ZeroRotator, SpawnLocation);
    GetWorld()->SpawnActor<AActor>(PointActorClass, Transform);
}
