#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FruitOfLife.generated.h"

UCLASS()
class PEKBGGAP_API AFruitOfLife : public AActor
{
    GENERATED_BODY()

public:
    AFruitOfLife();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateFruitOfLife();
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedCircles;

public:
    // Prefab/Blueprint to spawn for each circle
    UPROPERTY(EditAnywhere, Category = "FruitOfLife")
    TSubclassOf<AActor> CircleActorClass;

    // Radius parameter from the Unity script (cm). 100 = 1m
    UPROPERTY(EditAnywhere, Category = "FruitOfLife", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Spawning behavior
    UPROPERTY(EditAnywhere, Category = "FruitOfLife")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "FruitOfLife")
    bool bRebuildOnConstruction = true;
};

