#include "StructuralSymmetryAnalysisComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

UStructuralSymmetryAnalysisComponent::UStructuralSymmetryAnalysisComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralSymmetryAnalysisComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeStructures();
    const float SymmetryIndex = CalculateSymmetryIndex();
    UE_LOG(LogTemp, Log, TEXT("Symmetry Index (S): %.6f"), SymmetryIndex);
    VisualizeStructures();
}

void UStructuralSymmetryAnalysisComponent::InitializeStructures()
{
    LeftStructures.SetNum(NumberOfStructures);
    RightStructures.SetNum(NumberOfStructures);

    for (int32 Index = 0; Index < NumberOfStructures; ++Index)
    {
        LeftStructures[Index] = FMath::FRandRange(1.0f, 100.0f);
        RightStructures[Index] = FMath::FRandRange(1.0f, 100.0f);
    }
}

float UStructuralSymmetryAnalysisComponent::CalculateSymmetryIndex() const
{
    if (NumberOfStructures <= 0)
    {
        return 0.0f;
    }

    double Sum = 0.0;
    for (int32 Index = 0; Index < NumberOfStructures; ++Index)
    {
        const double Li = LeftStructures[Index];
        const double Ri = RightStructures[Index];
        const double Denominator = Li + Ri;
        if (Denominator > KINDA_SMALL_NUMBER)
        {
            Sum += FMath::Abs(Li - Ri) / Denominator;
        }
    }
    return static_cast<float>(Sum / NumberOfStructures);
}

void UStructuralSymmetryAnalysisComponent::VisualizeStructures() const
{
    if (!GetWorld())
    {
        return;
    }

    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

    for (int32 Index = 0; Index < NumberOfStructures; ++Index)
    {
        const FVector LeftPos = Origin + FVector(Index * 100.0f, LeftStructures[Index], 0.0f);
        const FVector RightPos = Origin + FVector(Index * 100.0f, RightStructures[Index], 100.0f);

        if (SphereActorClass)
        {
            GetWorld()->SpawnActor<AActor>(SphereActorClass, LeftPos, FRotator::ZeroRotator);
            GetWorld()->SpawnActor<AActor>(SphereActorClass, RightPos, FRotator::ZeroRotator);
        }
        else
        {
            DrawDebugSphere(GetWorld(), LeftPos, 10.0f, 8, FColor::Blue, true);
            DrawDebugSphere(GetWorld(), RightPos, 10.0f, 8, FColor::Red, true);
        }
    }
}
