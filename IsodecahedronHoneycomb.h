#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IsodecahedronHoneycomb.generated.h"

UCLASS()
class PEKBGGAP_API AIsodecahedronHoneycomb : public AActor
{
    GENERATED_BODY()

public:
    AIsodecahedronHoneycomb();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateHoneycomb();
    void CreateIsodecahedron(const FVector& Center);
    TArray<FVector> GenerateIsodecahedronVertices(const FVector& Center) const;
    TArray<FVector> GenerateHoneycombOffsets() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedEdges;

public:
    // Vertex and optional edge prefab equivalents
    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb")
    TSubclassOf<AActor> VertexActorClass;

    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb")
    TSubclassOf<AActor> EdgeActorClass; // optional

    // Size/spacing control (cm). Mirroring Unity, this affects spacing; vertex positions are unit-sized around centers.
    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb", meta = (ClampMin = "0"))
    int32 GridSize = 3;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb")
    FLinearColor LineColor = FLinearColor::Green;

    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // If an EdgeActorClass is provided, also spawn edge actors scaled to length
    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb", meta = (ClampMin = "0.0"))
    float EdgeThickness = 5.f; // cm, applied to Y/Z scales

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "IsodecahedronHoneycomb")
    bool bRebuildOnConstruction = true;
};

