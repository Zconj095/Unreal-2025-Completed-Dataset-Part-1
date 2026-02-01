#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeOfLife.generated.h"

UCLASS()
class PEKBGGAP_API ATreeOfLife : public AActor
{
    GENERATED_BODY()

public:
    ATreeOfLife();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateTreeOfLife();
    TArray<FVector> GenerateTreeOfLifePositions() const;
    void DrawEdges();
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    // Cached local positions (unit-based) before scaling by Radius
    UPROPERTY(Transient)
    TArray<FVector> CirclePositions;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedCircles;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedLines;

public:
    // Prefabs/Blueprints
    UPROPERTY(EditAnywhere, Category = "TreeOfLife")
    TSubclassOf<AActor> CircleActorClass;

    UPROPERTY(EditAnywhere, Category = "TreeOfLife")
    TSubclassOf<AActor> LineActorClass; // optional

    // Distance scale in cm (100 = 1m). Multiplies unit positions.
    UPROPERTY(EditAnywhere, Category = "TreeOfLife", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug line options
    UPROPERTY(EditAnywhere, Category = "TreeOfLife")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "TreeOfLife")
    FLinearColor LineColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, Category = "TreeOfLife", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // For LineActorClass: Y/Z thickness; X is edge length
    UPROPERTY(EditAnywhere, Category = "TreeOfLife", meta = (ClampMin = "0.0"))
    float LineThickness = 5.f;

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "TreeOfLife")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "TreeOfLife")
    bool bRebuildOnConstruction = true;
};

