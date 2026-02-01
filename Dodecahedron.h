#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dodecahedron.generated.h"

UCLASS()
class PEKBGGAP_API ADodecahedron : public AActor
{
    GENERATED_BODY()

public:
    ADodecahedron();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateDodecahedron();
    TArray<FVector> GenerateDodecahedronVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Actor class to spawn at each vertex (e.g., small sphere/cube blueprint)
    UPROPERTY(EditAnywhere, Category = "Dodecahedron")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor in Unreal units (cm). 100 = 1m.
    UPROPERTY(EditAnywhere, Category = "Dodecahedron", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Draw debug edges between vertices
    UPROPERTY(EditAnywhere, Category = "Dodecahedron")
    bool bDrawEdges = true;

    // Edge color and lifetime
    UPROPERTY(EditAnywhere, Category = "Dodecahedron")
    FLinearColor LineColor = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, Category = "Dodecahedron", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "Dodecahedron")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "Dodecahedron")
    bool bRebuildOnConstruction = true;
};

