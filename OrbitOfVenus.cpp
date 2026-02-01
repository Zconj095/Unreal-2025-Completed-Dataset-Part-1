#include "OrbitOfVenus.h"
#include "GameFramework/Actor.h"

#include "Components/SceneComponent.h"
#include "Engine/World.h"

AOrbitOfVenus::AOrbitOfVenus()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;
}

void AOrbitOfVenus::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnAtBeginPlay)
    {
        ClearSpawned();
        CreateOrbitPattern();
    }
}

#if WITH_EDITOR
void AOrbitOfVenus::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if (bRebuildOnConstruction)
    {
        ClearSpawned();
        CreateOrbitPattern();
    }
}
#endif

void AOrbitOfVenus::ClearSpawned()
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

void AOrbitOfVenus::CreateOrbitPattern()
{
    UWorld* World = GetWorld();
    if (!World || !CircleActorClass || NumCircles <= 0)
    {
        return;
    }

    const FVector Origin = GetActorLocation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 i = 0; i < NumCircles; ++i)
    {
        const float AngleRad = FMath::DegreesToRadians(i * RotationAngle);
        const FVector LocalPos(FMath::Cos(AngleRad) * Radius, FMath::Sin(AngleRad) * Radius, 0.f);

        const FVector WorldPos = Origin + LocalPos;
        const FTransform Xform(FRotator::ZeroRotator, WorldPos, FVector::OneVector);
        if (AActor* Spawned = World->SpawnActor<AActor>(CircleActorClass, Xform, SpawnParams))
        {
            Spawned->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            SpawnedCircles.Add(Spawned);
        }
    }
}
