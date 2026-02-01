#include "DoubleMerkaba.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ADoubleMerkaba::ADoubleMerkaba()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void ADoubleMerkaba::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateDoubleMerkaba();
    }
}

#if WITH_EDITOR
void ADoubleMerkaba::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateDoubleMerkaba();
    }
}
#endif

void ADoubleMerkaba::ClearSpawned()
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

void ADoubleMerkaba::CreateDoubleMerkaba()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const TArray<FVector> Vertices = GenerateMerkabaVertices();

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

TArray<FVector> ADoubleMerkaba::GenerateMerkabaVertices() const
{
    TArray<FVector> Vertices;
    Vertices.Reserve(16);

    const float Sqrt3Over2 = FMath::Sqrt(3.f) / 2.f;
    const float Sqrt2 = FMath::Sqrt(2.f);

    // Primary Star Tetrahedron (indices 0..3)
    Vertices.Add(FVector(0.f, 1.f, 0.f));                      // Top
    Vertices.Add(FVector(-Sqrt3Over2, -0.5f, 0.f));            // Bottom-left
    Vertices.Add(FVector( Sqrt3Over2, -0.5f, 0.f));            // Bottom-right
    Vertices.Add(FVector(0.f, -0.5f, Sqrt2));                  // Front

    // Inverted Star Tetrahedron (indices 4..7)
    Vertices.Add(FVector(0.f, -1.f, 0.f));                     // Bottom
    Vertices.Add(FVector(-Sqrt3Over2, 0.5f, 0.f));             // Top-left
    Vertices.Add(FVector( Sqrt3Over2, 0.5f, 0.f));             // Top-right
    Vertices.Add(FVector(0.f, 0.5f, -Sqrt2));                  // Back

    // Second inverted star for the "Double" Merkaba (indices 8..15)
    Vertices.Append({
        FVector(0.f, 2.f, 0.f),
        FVector(-Sqrt3Over2, 1.5f, 0.f),
        FVector( Sqrt3Over2, 1.5f, 0.f),
        FVector(0.f, 1.5f, Sqrt2),

        FVector(0.f, -2.f, 0.f),
        FVector(-Sqrt3Over2, -1.5f, 0.f),
        FVector( Sqrt3Over2, -1.5f, 0.f),
        FVector(0.f, -1.5f, -Sqrt2)
    });

    return Vertices;
}

void ADoubleMerkaba::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    // Matches the Unity edges definition (only first two tetrahedra + connections)
    static const int32 Edges[][2] = {
        // Primary Star Tetrahedron
        { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 2 }, { 2, 3 }, { 3, 1 },

        // Inverted Star Tetrahedron
        { 4, 5 }, { 4, 6 }, { 4, 7 }, { 5, 6 }, { 6, 7 }, { 7, 5 },

        // Connections between both
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }
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
