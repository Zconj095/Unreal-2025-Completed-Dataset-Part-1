#include "MetatronsCube.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AMetatronsCube::AMetatronsCube()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AMetatronsCube::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateMetatronsCube();
    }
}

#if WITH_EDITOR
void AMetatronsCube::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateMetatronsCube();
    }
}
#endif

void AMetatronsCube::ClearSpawned()
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

void AMetatronsCube::CreateMetatronsCube()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    CirclePositions = GenerateFruitOfLifePositions();

    const FVector Origin = GetActorLocation();

    if (CircleActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        for (const FVector& Local : CirclePositions)
        {
            const FVector WorldPos = Origin + Local;
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

TArray<FVector> AMetatronsCube::GenerateFruitOfLifePositions() const
{
    TArray<FVector> Positions;
    Positions.Reserve(13);

    const float Distance = Radius * FMath::Sqrt(3.f); // Distance between centers

    Positions.Add(FVector::ZeroVector); // Center

    // First ring
    Positions.Add(FVector(-Radius, 0.f, 0.f));                     // Left
    Positions.Add(FVector( Radius, 0.f, 0.f));                     // Right
    Positions.Add(FVector(-Radius * 0.5f,  Distance * 0.5f, 0.f)); // Top-left
    Positions.Add(FVector( Radius * 0.5f,  Distance * 0.5f, 0.f)); // Top-right
    Positions.Add(FVector(-Radius * 0.5f, -Distance * 0.5f, 0.f)); // Bottom-left
    Positions.Add(FVector( Radius * 0.5f, -Distance * 0.5f, 0.f)); // Bottom-right

    // Outer ring
    Positions.Add(FVector(0.f,  Distance, 0.f));                   // Top
    Positions.Add(FVector(0.f, -Distance, 0.f));                   // Bottom
    Positions.Add(FVector(-Radius,  Distance, 0.f));               // Top-left outer
    Positions.Add(FVector( Radius,  Distance, 0.f));               // Top-right outer
    Positions.Add(FVector(-Radius, -Distance, 0.f));               // Bottom-left outer
    Positions.Add(FVector( Radius, -Distance, 0.f));               // Bottom-right outer

    return Positions;
}

void AMetatronsCube::DrawEdges()
{
    UWorld* World = GetWorld();
    if (!World || CirclePositions.Num() == 0)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const bool bPersistent = DebugLineDuration > 0.f;
    const FColor Color = LineColor.ToFColor(true);

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 i = 0; i < CirclePositions.Num(); ++i)
    {
        for (int32 j = i + 1; j < CirclePositions.Num(); ++j)
        {
            const FVector Start = Origin + CirclePositions[i];
            const FVector End   = Origin + CirclePositions[j];

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
}
