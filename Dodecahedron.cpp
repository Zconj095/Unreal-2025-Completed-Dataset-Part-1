#include "Dodecahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ADodecahedron::ADodecahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void ADodecahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateDodecahedron();
    }
}

#if WITH_EDITOR
void ADodecahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateDodecahedron();
    }
}
#endif

void ADodecahedron::ClearSpawned()
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

void ADodecahedron::CreateDodecahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();

    const TArray<FVector> Vertices = GenerateDodecahedronVertices();

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

TArray<FVector> ADodecahedron::GenerateDodecahedronVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(20);

    const float Phi = (1.f + FMath::Sqrt(5.f)) / 2.f;

    Vertices.Append({
        FVector(-1, -1, -1),
        FVector(-1, -1,  1),
        FVector(-1,  1, -1),
        FVector(-1,  1,  1),
        FVector( 1, -1, -1),
        FVector( 1, -1,  1),
        FVector( 1,  1, -1),
        FVector( 1,  1,  1),
        FVector( 0, -1 / Phi, -Phi),
        FVector( 0, -1 / Phi,  Phi),
        FVector( 0,  1 / Phi, -Phi),
        FVector( 0,  1 / Phi,  Phi),
        FVector(-1 / Phi, -Phi,  0),
        FVector(-1 / Phi,  Phi,  0),
        FVector( 1 / Phi, -Phi,  0),
        FVector( 1 / Phi,  Phi,  0),
        FVector(-Phi,  0, -1 / Phi),
        FVector(-Phi,  0,  1 / Phi),
        FVector( Phi,  0, -1 / Phi),
        FVector( Phi,  0,  1 / Phi)
    });

    return Vertices;
}

void ADodecahedron::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 1 }, { 0, 2 }, { 0, 4 }, { 0, 8 }, { 0, 10 },
        { 1, 3 }, { 1, 5 }, { 1, 9 }, { 1, 11 },
        { 2, 3 }, { 2, 6 }, { 2, 10 }, { 2, 12 },
        { 3, 7 }, { 3, 11 }, { 3, 13 },
        { 4, 5 }, { 4, 6 }, { 4, 8 }, { 4, 14 },
        { 5, 7 }, { 5, 9 }, { 5, 15 },
        { 6, 7 }, { 6, 12 }, { 6, 14 },
        { 7, 13 }, { 7, 15 },
        { 8, 9 }, { 8, 14 },
        { 9, 15 },
        { 10, 11 }, { 10, 12 },
        { 11, 13 },
        { 12, 13 }, { 12, 14 },
        { 13, 15 },
        { 14, 15 },
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
