#include "Tetrahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATetrahedron::ATetrahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void ATetrahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateTetrahedron();
    }
}

#if WITH_EDITOR
void ATetrahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateTetrahedron();
    }
}
#endif

void ATetrahedron::ClearSpawned()
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

void ATetrahedron::CreateTetrahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Vertices = GenerateTetrahedronVertices();

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

TArray<FVector> ATetrahedron::GenerateTetrahedronVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(4);

    const float Sqrt3Over2 = FMath::Sqrt(3.f) / 2.f;
    const float Half = 0.5f;
    const float Sqrt2 = FMath::Sqrt(2.f);

    // Unit-based positions that will be scaled by Radius
    Vertices.Append({
        FVector(0.f, 1.f, 0.f),                 // Top
        FVector(-Sqrt3Over2, -Half, 0.f),       // Bottom-left
        FVector( Sqrt3Over2, -Half, 0.f),       // Bottom-right
        FVector(0.f, -Half, Sqrt2)              // Back
    });

    return Vertices;
}

void ATetrahedron::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 1 }, { 0, 2 }, { 0, 3 }, // From top
        { 1, 2 }, { 2, 3 }, { 3, 1 }  // Base edges
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
