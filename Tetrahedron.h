#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tetrahedron.generated.h"

UCLASS()
class PEKBGGAP_API ATetrahedron : public AActor
{
    GENERATED_BODY()

public:
    ATetrahedron();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateTetrahedron();
    TArray<FVector> GenerateTetrahedronVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Prefab/Blueprint to spawn at each vertex
    UPROPERTY(EditAnywhere, Category = "Tetrahedron")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor (cm). Multiplies the unit coordinates (100 = 1m)
    UPROPERTY(EditAnywhere, Category = "Tetrahedron", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edges
    UPROPERTY(EditAnywhere, Category = "Tetrahedron")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "Tetrahedron")
    FLinearColor LineColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, Category = "Tetrahedron", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "Tetrahedron")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "Tetrahedron")
    bool bRebuildOnConstruction = true;
};

