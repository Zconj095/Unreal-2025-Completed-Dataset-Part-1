#include "IsodecahedronHoneycomb.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AIsodecahedronHoneycomb::AIsodecahedronHoneycomb()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AIsodecahedronHoneycomb::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateHoneycomb();
    }
}

#if WITH_EDITOR
void AIsodecahedronHoneycomb::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateHoneycomb();
    }
}
#endif

void AIsodecahedronHoneycomb::ClearSpawned()
{
    for (TWeakObjectPtr<AActor>& Weak : SpawnedVertices)
    {
        if (AActor* A = Weak.Get())
        {
            if (IsValid(A))
            {
                A->Destroy();
            }
        }
    }
    SpawnedVertices.Empty();

    for (TWeakObjectPtr<AActor>& Weak : SpawnedEdges)
    {
        if (AActor* A = Weak.Get())
        {
            if (IsValid(A))
            {
                A->Destroy();
            }
        }
    }
    SpawnedEdges.Empty();
}

void AIsodecahedronHoneycomb::CreateHoneycomb()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Offsets = GenerateHoneycombOffsets();

    // Note: mirroring the Unity script, multiply offset by Radius again when applying to center
    for (const FVector& Off : Offsets)
    {
        const FVector Center = Origin + Off * Radius;
        CreateIsodecahedron(Center);
    }
}

void AIsodecahedronHoneycomb::CreateIsodecahedron(const FVector& Center)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const TArray<FVector> Vertices = GenerateIsodecahedronVertices(Center);

    if (VertexActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        for (const FVector& P : Vertices)
        {
            const FTransform Xform(FRotator::ZeroRotator, P, FVector::OneVector);
            if (AActor* Spawned = World->SpawnActor<AActor>(VertexActorClass, Xform, SpawnParams))
            {
                Spawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                SpawnedVertices.Add(Spawned);
            }
        }
    }

    if (bDrawEdges)
    {
        DrawEdges(Vertices);
    }
}

TArray<FVector> AIsodecahedronHoneycomb::GenerateIsodecahedronVertices(const FVector& Center) const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(12);

    const float Phi = (1.f + FMath::Sqrt(5.f)) / 2.f;

    Vertices.Append({
        Center + FVector(0.f, 1.f,  Phi), Center + FVector(0.f, -1.f,  Phi),
        Center + FVector(0.f, 1.f, -Phi), Center + FVector(0.f, -1.f, -Phi),
        Center + FVector(1.f,  Phi, 0.f), Center + FVector(-1.f,  Phi, 0.f),
        Center + FVector(1.f, -Phi, 0.f), Center + FVector(-1.f, -Phi, 0.f),
        Center + FVector( Phi, 0.f, 1.f), Center + FVector(-Phi, 0.f, 1.f),
        Center + FVector( Phi, 0.f, -1.f), Center + FVector(-Phi, 0.f, -1.f)
    });

    return Vertices;
}

TArray<FVector> AIsodecahedronHoneycomb::GenerateHoneycombOffsets() const
{
    TArray<FVector> Offsets;
    const float Offset = Radius * FMath::Sqrt(3.f);

    for (int32 X = -GridSize; X <= GridSize; ++X)
    {
        for (int32 Y = -GridSize; Y <= GridSize; ++Y)
        {
            for (int32 Z = -GridSize; Z <= GridSize; ++Z)
            {
                if (((X + Y + Z) % 2) == 0)
                {
                    Offsets.Add(FVector(
                        X * Radius * 1.5f,
                        Y * Offset,
                        Z * Offset
                    ));
                }
            }
        }
    }

    return Offsets;
}

void AIsodecahedronHoneycomb::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 1 }, { 0, 2 }, { 0, 4 }, { 0, 8 }, { 0, 9 },
        { 1, 3 }, { 1, 6 }, { 1, 8 }, { 1, 9 },
        { 2, 3 }, { 2, 4 }, { 2, 10 }, { 2, 11 },
        { 3, 6 }, { 3, 10 }, { 3, 11 },
        { 4, 5 }, { 4, 8 }, { 4, 10 },
        { 5, 7 }, { 5, 8 }, { 5, 9 }, { 5, 11 },
        { 6, 7 }, { 6, 9 }, { 6, 10 },
        { 7, 9 }, { 7, 11 },
        { 8, 10 }, { 9, 11 }
    };

    const bool bPersistent = DebugLineDuration > 0.f;
    const FColor Color = LineColor.ToFColor(true);

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (size_t i = 0; i < UE_ARRAY_COUNT(Edges); ++i)
    {
        const int32 I0 = Edges[i][0];
        const int32 I1 = Edges[i][1];
        if (!Vertices.IsValidIndex(I0) || !Vertices.IsValidIndex(I1))
        {
            continue;
        }

        const FVector Start = Vertices[I0];
        const FVector End   = Vertices[I1];

        if (bDrawEdges)
        {
            DrawDebugLine(World, Start, End, Color, bPersistent, DebugLineDuration, 0, 1.5f);
        }

        if (EdgeActorClass)
        {
            const FVector Mid = (Start + End) * 0.5f;
            const FVector Dir = (End - Start).GetSafeNormal();
            const float Len = (End - Start).Size();

            const FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
            const FTransform Xform(Rot, Mid, FVector(Len, EdgeThickness, EdgeThickness));

            if (AActor* Edge = World->SpawnActor<AActor>(EdgeActorClass, Xform, SpawnParams))
            {
                Edge->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                SpawnedEdges.Add(Edge);
            }
        }
    }
}
