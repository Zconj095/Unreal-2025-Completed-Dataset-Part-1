#include "FruitOfLife.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"

AFruitOfLife::AFruitOfLife()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AFruitOfLife::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateFruitOfLife();
    }
}

#if WITH_EDITOR
void AFruitOfLife::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateFruitOfLife();
    }
}
#endif

void AFruitOfLife::ClearSpawned()
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

void AFruitOfLife::CreateFruitOfLife()
{
    UWorld* World = GetWorld();
    if (!World || !CircleActorClass)
    {
        return;
    }

    const FVector Origin = GetActorLocation();

    const float Distance = Radius * FMath::Sqrt(3.f); // distance between circle centers

    const TArray<FVector> Offsets = {
        FVector::ZeroVector,                                   // Center
        FVector(-Radius, 0.f, 0.f),                            // Left
        FVector( Radius, 0.f, 0.f),                            // Right
        FVector(-Radius * 0.5f,  Distance * 0.5f, 0.f),        // Top-left
        FVector( Radius * 0.5f,  Distance * 0.5f, 0.f),        // Top-right
        FVector(-Radius * 0.5f, -Distance * 0.5f, 0.f),        // Bottom-left
        FVector( Radius * 0.5f, -Distance * 0.5f, 0.f),        // Bottom-right
        FVector(0.f,  Distance, 0.f),                          // Top
        FVector(0.f, -Distance, 0.f),                          // Bottom
        FVector(-Radius,  Distance, 0.f),                      // Top-left outer
        FVector( Radius,  Distance, 0.f),                      // Top-right outer
        FVector(-Radius, -Distance, 0.f),                      // Bottom-left outer
        FVector( Radius, -Distance, 0.f)                       // Bottom-right outer
    };

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (const FVector& Local : Offsets)
    {
        const FVector WorldPos = Origin + Local;
        const FTransform SpawnXform(FRotator::ZeroRotator, WorldPos, FVector::OneVector);
        if (AActor* Spawned = World->SpawnActor<AActor>(CircleActorClass, SpawnXform, SpawnParams))
        {
            Spawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            SpawnedCircles.Add(Spawned);
        }
    }
}
