#include "Icosidodecahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AIcosidodecahedron::AIcosidodecahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AIcosidodecahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateIcosidodecahedron();
    }
}

#if WITH_EDITOR
void AIcosidodecahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateIcosidodecahedron();
    }
}
#endif

void AIcosidodecahedron::ClearSpawned()
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

void AIcosidodecahedron::CreateIcosidodecahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Vertices = GenerateIcosidodecahedronVertices();

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

TArray<FVector> AIcosidodecahedron::GenerateIcosidodecahedronVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(20);

    const float Phi = (1.f + FMath::Sqrt(5.f)) / 2.f;

    Vertices.Append({
        // Icosahedron vertices
        FVector(0.f, 1.f,  Phi), FVector(0.f, -1.f,  Phi),
        FVector(0.f, 1.f, -Phi), FVector(0.f, -1.f, -Phi),
        FVector(1.f,  Phi, 0.f), FVector(-1.f,  Phi, 0.f),
        FVector(1.f, -Phi, 0.f), FVector(-1.f, -Phi, 0.f),
        FVector( Phi, 0.f, 1.f), FVector(-Phi, 0.f, 1.f),
        FVector( Phi, 0.f, -1.f), FVector(-Phi, 0.f, -1.f),

        // Midpoints of dodecahedron edges
        FVector( 0.5f,  0.5f * Phi,  0.5f * Phi),
        FVector(-0.5f,  0.5f * Phi,  0.5f * Phi),
        FVector( 0.5f, -0.5f * Phi,  0.5f * Phi),
        FVector(-0.5f, -0.5f * Phi,  0.5f * Phi),
        FVector( 0.5f,  0.5f * Phi, -0.5f * Phi),
        FVector(-0.5f,  0.5f * Phi, -0.5f * Phi),
        FVector( 0.5f, -0.5f * Phi, -0.5f * Phi),
        FVector(-0.5f, -0.5f * Phi, -0.5f * Phi)
    });

    return Vertices;
}

void AIcosidodecahedron::DrawEdges(const TArray<FVector>& Vertices)
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
