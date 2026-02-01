#include "StructuralSymmetryComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

UStructuralSymmetryComponent::UStructuralSymmetryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralSymmetryComponent::OnComponentCreated()
{
    Super::OnComponentCreated();
    LeftStructures.Init(0.0f, NumStructures);
    RightStructures.Init(0.0f, NumStructures);
}

void UStructuralSymmetryComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeStructures();

    const float SymmetryIndex = CalculateSymmetryIndex();
    UE_LOG(LogTemp, Log, TEXT("Symmetry Index (S): %.6f"), SymmetryIndex);

    VisualizeStructures();
}

void UStructuralSymmetryComponent::InitializeStructures()
{
    for (int32 Index = 0; Index < NumStructures; ++Index)
    {
        LeftStructures[Index] = FMath::FRandRange(0.0f, 100.0f);
        RightStructures[Index] = FMath::FRandRange(0.0f, 100.0f);
    }
}

float UStructuralSymmetryComponent::CalculateSymmetryIndex() const
{
    if (NumStructures <= 0)
    {
        return 0.0f;
    }

    double Sum = 0.0;

    for (int32 Index = 0; Index < NumStructures; ++Index)
    {
        const double Li = LeftStructures[Index];
        const double Ri = RightStructures[Index];
        const double Denominator = Li + Ri;
        if (Denominator > KINDA_SMALL_NUMBER)
        {
            Sum += FMath::Abs(Li - Ri) / Denominator;
        }
    }

    return static_cast<float>(Sum / NumStructures);
}

void UStructuralSymmetryComponent::VisualizeStructures() const
{
    if (!GetWorld())
    {
        return;
    }

    UWorld* World = GetWorld();
    for (int32 Index = 0; Index < NumStructures; ++Index)
    {
        const FVector LeftPos = FVector(Index * 10.0f, LeftStructures[Index], 0.0f);
        const FVector RightPos = FVector(Index * 10.0f, RightStructures[Index], 100.0f);

        if (SphereActorClass)
        {
            World->SpawnActor<AActor>(SphereActorClass, LeftPos, FRotator::ZeroRotator);
            World->SpawnActor<AActor>(SphereActorClass, RightPos, FRotator::ZeroRotator);
        }
        else
        {
            DrawDebugSphere(World, LeftPos, 10.0f, 8, FColor::Blue, true, 60.0f);
            DrawDebugSphere(World, RightPos, 10.0f, 8, FColor::Red, true, 60.0f);
        }
    }
}
