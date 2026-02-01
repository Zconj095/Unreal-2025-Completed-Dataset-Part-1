#include "Octahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AOctahedron::AOctahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AOctahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateOctahedron();
    }
}

#if WITH_EDITOR
void AOctahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateOctahedron();
    }
}
#endif

void AOctahedron::ClearSpawned()
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
}

void AOctahedron::CreateOctahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Vertices = GenerateOctahedronVertices();

    // Spawn vertex actors
    if (VertexActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        for (const FVector& V : Vertices)
        {
            const FVector WorldPos = Origin + V * Radius;
            const FTransform SpawnXform(FRotator::ZeroRotator, WorldPos, FVector::OneVector);
            if (AActor* Spawned = World->SpawnActor<AActor>(VertexActorClass, SpawnXform, SpawnParams))
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

TArray<FVector> AOctahedron::GenerateOctahedronVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(6);

    // Unit octahedron vertices
    Vertices.Add(FVector(0.f, 1.f, 0.f));   // Top
    Vertices.Add(FVector(0.f, -1.f, 0.f));  // Bottom
    Vertices.Add(FVector(1.f, 0.f, 0.f));   // Right
    Vertices.Add(FVector(-1.f, 0.f, 0.f));  // Left
    Vertices.Add(FVector(0.f, 0.f, 1.f));   // Front
    Vertices.Add(FVector(0.f, 0.f, -1.f));  // Back

    return Vertices;
}

void AOctahedron::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, // Top to others
        { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, // Bottom to others
        { 2, 4 }, { 4, 3 }, { 3, 5 }, { 5, 2 }  // Base edges
    };

    const FVector Origin = GetActorLocation();
    const bool bPersistent = DebugLineDuration > 0.f;
    const FColor Color = LineColor.ToFColor(true);

    for (size_t i = 0; i < UE_ARRAY_COUNT(Edges); ++i)
    {
        const int32 I0 = Edges[i][0];
        const int32 I1 = Edges[i][1];
        if (!Vertices.IsValidIndex(I0) || !Vertices.IsValidIndex(I1))
        {
            continue;
        }

        const FVector Start = Origin + Vertices[I0] * Radius;
        const FVector End   = Origin + Vertices[I1] * Radius;
        DrawDebugLine(World, Start, End, Color, bPersistent, DebugLineDuration, 0, 1.5f);
    }
}
