#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MetatronsCube.generated.h"

UCLASS()
class PEKBGGAP_API AMetatronsCube : public AActor
{
    GENERATED_BODY()

public:
    AMetatronsCube();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateMetatronsCube();
    TArray<FVector> GenerateFruitOfLifePositions() const;
    void DrawEdges();
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    // Cached positions of circles (local offsets)
    UPROPERTY(Transient)
    TArray<FVector> CirclePositions;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedCircles;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedLines;

public:
    // Prefab/Blueprints for circles and optional lines
    UPROPERTY(EditAnywhere, Category = "MetatronsCube")
    TSubclassOf<AActor> CircleActorClass;

    UPROPERTY(EditAnywhere, Category = "MetatronsCube")
    TSubclassOf<AActor> LineActorClass; // optional

    // Circle radius parameter from Unity (cm). 100 = 1m
    UPROPERTY(EditAnywhere, Category = "MetatronsCube", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "MetatronsCube")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "MetatronsCube")
    FLinearColor LineColor = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, Category = "MetatronsCube", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Thickness for spawned LineActorClass (Y/Z scale). X-scale is edge length.
    UPROPERTY(EditAnywhere, Category = "MetatronsCube", meta = (ClampMin = "0.0"))
    float LineThickness = 5.f; // cm

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "MetatronsCube")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "MetatronsCube")
    bool bRebuildOnConstruction = true;
};

