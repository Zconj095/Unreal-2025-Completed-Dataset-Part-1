#include "Icosahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AIcosahedron::AIcosahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AIcosahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateIcosahedron();
    }
}

#if WITH_EDITOR
void AIcosahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateIcosahedron();
    }
}
#endif

void AIcosahedron::ClearSpawned()
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

void AIcosahedron::CreateIcosahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Vertices = GenerateIcosahedronVertices();

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

TArray<FVector> AIcosahedron::GenerateIcosahedronVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(12);

    const float Phi = (1.f + FMath::Sqrt(5.f)) / 2.f; // golden ratio

    Vertices.Append({
        FVector(-1.f,  Phi,  0.f),
        FVector( 1.f,  Phi,  0.f),
        FVector(-1.f, -Phi,  0.f),
        FVector( 1.f, -Phi,  0.f),

        FVector( 0.f, -1.f,  Phi),
        FVector( 0.f,  1.f,  Phi),
        FVector( 0.f, -1.f, -Phi),
        FVector( 0.f,  1.f, -Phi),

        FVector( Phi,  0.f, -1.f),
        FVector( Phi,  0.f,  1.f),
        FVector(-Phi,  0.f, -1.f),
        FVector(-Phi,  0.f,  1.f)
    });

    return Vertices;
}

void AIcosahedron::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 1 }, { 0, 5 }, { 0, 7 }, { 0, 10 }, { 0, 11 },
        { 1, 5 }, { 1, 7 }, { 1, 8 }, { 1, 9 },
        { 2, 3 }, { 2, 4 }, { 2, 6 }, { 2, 10 }, { 2, 11 },
        { 3, 4 }, { 3, 6 }, { 3, 8 }, { 3, 9 },
        { 4, 5 }, { 4, 9 },
        { 5, 11 },
        { 6, 7 }, { 6, 10 },
        { 7, 8 },
        { 8, 9 },
        { 10, 11 }
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
