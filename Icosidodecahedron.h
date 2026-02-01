#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Icosidodecahedron.generated.h"

UCLASS()
class PEKBGGAP_API AIcosidodecahedron : public AActor
{
    GENERATED_BODY()

public:
    AIcosidodecahedron();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateIcosidodecahedron();
    TArray<FVector> GenerateIcosidodecahedronVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Actor class to spawn at each vertex
    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor in cm (100 = 1m)
    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug line rendering
    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron")
    FLinearColor LineColor = FLinearColor(0.f, 1.f, 1.f, 1.f);

    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "Icosidodecahedron")
    bool bRebuildOnConstruction = true;
};
