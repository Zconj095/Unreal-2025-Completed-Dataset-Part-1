#include "TreeOfLife.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATreeOfLife::ATreeOfLife()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void ATreeOfLife::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateTreeOfLife();
    }
}

#if WITH_EDITOR
void ATreeOfLife::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateTreeOfLife();
    }
}
#endif

void ATreeOfLife::ClearSpawned()
{
    for (TWeakObjectPtr<AActor>& Weak : SpawnedCircles)
    {
        if (AActor* A = Weak.Get())
        {
            if (IsValid(A))
            {
                A->Destroy();
            }
        }
    }
    SpawnedCircles.Empty();

    for (TWeakObjectPtr<AActor>& Weak : SpawnedLines)
    {
        if (AActor* A = Weak.Get())
        {
            if (IsValid(A))
            {
                A->Destroy();
            }
        }
    }
    SpawnedLines.Empty();

    CirclePositions.Reset();
}

void ATreeOfLife::CreateTreeOfLife()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    CirclePositions = GenerateTreeOfLifePositions();

    const FVector Origin = GetActorLocation();

    if (CircleActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        for (const FVector& LocalUnit : CirclePositions)
        {
            const FVector WorldPos = Origin + LocalUnit * Radius;
            const FTransform Xform(FRotator::ZeroRotator, WorldPos, FVector::OneVector);
            if (AActor* Spawned = World->SpawnActor<AActor>(CircleActorClass, Xform, SpawnParams))
            {
                Spawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                SpawnedCircles.Add(Spawned);
            }
        }
    }

    DrawEdges();
}

TArray<FVector> ATreeOfLife::GenerateTreeOfLifePositions() const
{
    TArray<FVector> Positions;
    Positions.Reserve(10);

    Positions.Append({
        FVector(0.f,  4.f, 0.f), // Top
        FVector(0.f,  3.f, 0.f),
        FVector(-1.f, 2.f, 0.f),
        FVector( 1.f, 2.f, 0.f),
        FVector(0.f,  1.f, 0.f),
        FVector(-1.f, 0.f, 0.f),
        FVector( 1.f, 0.f, 0.f),
        FVector(0.f, -1.f, 0.f),
        FVector(-0.5f, -2.f, 0.f),
        FVector( 0.5f, -2.f, 0.f) // Bottom pair
    });

    return Positions;
}

void ATreeOfLife::DrawEdges()
{
    UWorld* World = GetWorld();
    if (!World || CirclePositions.Num() == 0)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 1 }, { 1, 2 }, { 1, 3 },
        { 2, 4 }, { 3, 4 }, { 4, 5 },
        { 4, 6 }, { 5, 7 }, { 6, 7 },
        { 7, 8 }, { 7, 9 }
    };

    const FVector Origin = GetActorLocation();
    const bool bPersistent = DebugLineDuration > 0.f;
    const FColor Color = LineColor.ToFColor(true);

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (size_t i = 0; i < UE_ARRAY_COUNT(Edges); ++i)
    {
        const int32 I0 = Edges[i][0];
        const int32 I1 = Edges[i][1];
        if (!CirclePositions.IsValidIndex(I0) || !CirclePositions.IsValidIndex(I1))
        {
            continue;
        }

        const FVector Start = Origin + CirclePositions[I0] * Radius;
        const FVector End   = Origin + CirclePositions[I1] * Radius;

        if (bDrawEdges)
        {
            DrawDebugLine(World, Start, End, Color, bPersistent, DebugLineDuration, 0, 1.5f);
        }

        if (LineActorClass)
        {
            const FVector Mid = (Start + End) * 0.5f;
            const FVector Dir = (End - Start).GetSafeNormal();
            const float Len = (End - Start).Size();
            const FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
            const FTransform Xform(Rot, Mid, FVector(Len, LineThickness, LineThickness));

            if (AActor* Line = World->SpawnActor<AActor>(LineActorClass, Xform, SpawnParams))
            {
                Line->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                SpawnedLines.Add(Line);
            }
        }
    }
}
