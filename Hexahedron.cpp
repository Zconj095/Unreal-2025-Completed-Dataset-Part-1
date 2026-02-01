#include "Hexahedron.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AHexahedron::AHexahedron()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AHexahedron::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateHexahedron();
    }
}

#if WITH_EDITOR
void AHexahedron::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateHexahedron();
    }
}
#endif

void AHexahedron::ClearSpawned()
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

void AHexahedron::CreateHexahedron()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetActorLocation();

    // Define the 8 cube corners using Radius for offset
    const TArray<FVector> Vertices = {
        FVector(-Radius, -Radius, -Radius),  // 0 Bottom-left-front
        FVector( Radius, -Radius, -Radius),  // 1 Bottom-right-front
        FVector( Radius,  Radius, -Radius),  // 2 Top-right-front
        FVector(-Radius,  Radius, -Radius),  // 3 Top-left-front
        FVector(-Radius, -Radius,  Radius),  // 4 Bottom-left-back
        FVector( Radius, -Radius,  Radius),  // 5 Bottom-right-back
        FVector( Radius,  Radius,  Radius),  // 6 Top-right-back
        FVector(-Radius,  Radius,  Radius)   // 7 Top-left-back
    };

    // Spawn vertex actors
    if (VertexActorClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        for (const FVector& Local : Vertices)
        {
            const FVector WorldPos = Origin + Local;
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

void AHexahedron::DrawEdges(const TArray<FVector>& Vertices)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    static const int32 Edges[][2] = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, // Front face
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, // Back face
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }  // Connecting edges
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

        const FVector Start = Origin + Vertices[I0];
        const FVector End   = Origin + Vertices[I1];
        DrawDebugLine(World, Start, End, Color, bPersistent, DebugLineDuration, 0, 1.5f);
    }
}
