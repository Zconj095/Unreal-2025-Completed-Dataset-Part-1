#include "TwelvePointedStarTetrahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATwelvePointedStarTetrahedron::ATwelvePointedStarTetrahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void ATwelvePointedStarTetrahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateStarTetrahedron();
    }
}

#if WITH_EDITOR
void ATwelvePointedStarTetrahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateStarTetrahedron();
    }
}
#endif

void ATwelvePointedStarTetrahedron::ClearSpawned()
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

void ATwelvePointedStarTetrahedron::CreateStarTetrahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Vertices = GenerateStarVertices();

    // Spawn vertex actors
    if (VertexActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        for (const FVector& V : Vertices)
        {
            const FVector WorldPos = Origin + V * Radius;
            const FTransform Xform(FRotator::ZeroRotator, WorldPos, FVector::OneVector);
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

TArray<FVector> ATwelvePointedStarTetrahedron::GenerateStarVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(12);

    const float Factor = FMath::Sqrt(2.f) * 0.5f; // sqrt(2)/2

    Vertices.Append({
        // Main cube corners (±1, ±1, ±1)
        FVector( 1.f,  1.f,  1.f), FVector(-1.f,  1.f,  1.f),
        FVector( 1.f, -1.f,  1.f), FVector(-1.f, -1.f,  1.f),
        FVector( 1.f,  1.f, -1.f), FVector(-1.f,  1.f, -1.f),
        FVector( 1.f, -1.f, -1.f), FVector(-1.f, -1.f, -1.f),

        // Secondary vertices
        FVector(0.f,  Factor, -Factor), FVector(0.f, -Factor,  Factor),
        FVector( Factor, 0.f,  Factor), FVector(-Factor, 0.f, -Factor)
    });

    return Vertices;
}

void ATwelvePointedStarTetrahedron::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const bool bPersistent = DebugLineDuration > 0.f;
    const FColor Color = LineColor.ToFColor(true);

    for (int32 i = 0; i < Vertices.Num(); ++i)
    {
        for (int32 j = i + 1; j < Vertices.Num(); ++j)
        {
            const FVector Start = Origin + Vertices[i] * Radius;
            const FVector End   = Origin + Vertices[j] * Radius;
            DrawDebugLine(World, Start, End, Color, bPersistent, DebugLineDuration, 0, 1.5f);
        }
    }
}
