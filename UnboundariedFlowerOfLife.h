#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnboundariedFlowerOfLife.generated.h"

UCLASS()
class PEKBGGAP_API AUnboundariedFlowerOfLife : public AActor
{
    GENERATED_BODY()

public:
    AUnboundariedFlowerOfLife();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateUnboundariedFlowerOfLife();
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedCircles;

public:
    // Prefab/Blueprint to spawn for each circle
    UPROPERTY(EditAnywhere, Category = "FlowerOfLife")
    TSubclassOf<AActor> CircleActorClass;

    // Radius of each circle center spacing (cm; 100 = 1m)
    UPROPERTY(EditAnywhere, Category = "FlowerOfLife", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Grid half-extent in both axes
    UPROPERTY(EditAnywhere, Category = "FlowerOfLife", meta = (ClampMin = "0"))
    int32 GridSize = 5;

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "FlowerOfLife")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "FlowerOfLife")
    bool bRebuildOnConstruction = true;
};

