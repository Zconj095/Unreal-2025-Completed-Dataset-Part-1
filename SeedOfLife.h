#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeedOfLife.generated.h"

UCLASS()
class PEKBGGAP_API ASeedOfLife : public AActor
{
    GENERATED_BODY()

public:
    ASeedOfLife();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateSeedOfLife();
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedCircles;

public:
    // Prefab/Blueprint to spawn for each circle
    UPROPERTY(EditAnywhere, Category = "SeedOfLife")
    TSubclassOf<AActor> CircleActorClass;

    // Radius parameter from the Unity script (cm). 100 = 1m
    UPROPERTY(EditAnywhere, Category = "SeedOfLife", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Spawning behavior
    UPROPERTY(EditAnywhere, Category = "SeedOfLife")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "SeedOfLife")
    bool bRebuildOnConstruction = true;
};

