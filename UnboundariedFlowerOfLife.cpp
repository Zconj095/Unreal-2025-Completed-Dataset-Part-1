#include "UnboundariedFlowerOfLife.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"

AUnboundariedFlowerOfLife::AUnboundariedFlowerOfLife()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AUnboundariedFlowerOfLife::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateUnboundariedFlowerOfLife();
    }
}

#if WITH_EDITOR
void AUnboundariedFlowerOfLife::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateUnboundariedFlowerOfLife();
    }
}
#endif

void AUnboundariedFlowerOfLife::ClearSpawned()
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
}

void AUnboundariedFlowerOfLife::CreateUnboundariedFlowerOfLife()
{
    UWorld* World = GetWorld();
    if (!World || !CircleActorClass)
    {
        return;
    }

    const FVector Origin = GetActorLocation();
    const float Offset = Radius * FMath::Sqrt(3.f);

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 X = -GridSize; X <= GridSize; ++X)
    {
        for (int32 Y = -GridSize; Y <= GridSize; ++Y)
        {
            const float Px = X * Radius * 1.5f;
            const float Py = Y * Offset + ((X % 2 == 0) ? 0.f : Offset * 0.5f);
            const FVector Local(Px, Py, 0.f); // XY plane

            const FVector WorldPos = Origin + Local;
            const FTransform Xform(FRotator::ZeroRotator, WorldPos, FVector::OneVector);
            if (AActor* Spawned = World->SpawnActor<AActor>(CircleActorClass, Xform, SpawnParams))
            {
                Spawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                SpawnedCircles.Add(Spawned);
            }
        }
    }
}
