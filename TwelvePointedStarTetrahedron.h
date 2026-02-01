#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwelvePointedStarTetrahedron.generated.h"

UCLASS()
class PEKBGGAP_API ATwelvePointedStarTetrahedron : public AActor
{
    GENERATED_BODY()

public:
    ATwelvePointedStarTetrahedron();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateStarTetrahedron();
    TArray<FVector> GenerateStarVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Prefab/Blueprint to spawn for each vertex
    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor in cm (100 = 1m)
    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron")
    FLinearColor LineColor = FLinearColor::Yellow;

    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "TwelvePointedStarTetrahedron")
    bool bRebuildOnConstruction = true;
};

