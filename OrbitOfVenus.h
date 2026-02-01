#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbitOfVenus.generated.h"

UCLASS()
class PEKBGGAP_API AOrbitOfVenus : public AActor
{
    GENERATED_BODY()

public:
    AOrbitOfVenus();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateOrbitPattern();
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedCircles;

public:
    // Prefab/Blueprint to spawn for each circle
    UPROPERTY(EditAnywhere, Category = "OrbitOfVenus")
    TSubclassOf<AActor> CircleActorClass;

    // Number of circles and angular spacing (degrees)
    UPROPERTY(EditAnywhere, Category = "OrbitOfVenus", meta = (ClampMin = "0"))
    int32 NumCircles = 5;

    UPROPERTY(EditAnywhere, Category = "OrbitOfVenus")
    float RotationAngle = 72.f; // degrees (360 / NumCircles)

    // Radius of the ring in cm (100 = 1m)
    UPROPERTY(EditAnywhere, Category = "OrbitOfVenus", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "OrbitOfVenus")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "OrbitOfVenus")
    bool bRebuildOnConstruction = true;
};

