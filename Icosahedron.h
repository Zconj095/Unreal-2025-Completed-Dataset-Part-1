#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Icosahedron.generated.h"

UCLASS()
class PEKBGGAP_API AIcosahedron : public AActor
{
    GENERATED_BODY()

public:
    AIcosahedron();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateIcosahedron();
    TArray<FVector> GenerateIcosahedronVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Actor class to spawn for each vertex
    UPROPERTY(EditAnywhere, Category = "Icosahedron")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor in cm (100 = 1m)
    UPROPERTY(EditAnywhere, Category = "Icosahedron", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "Icosahedron")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "Icosahedron")
    FLinearColor LineColor = FLinearColor(1.f, 0.f, 1.f); // Magenta

    UPROPERTY(EditAnywhere, Category = "Icosahedron", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "Icosahedron")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "Icosahedron")
    bool bRebuildOnConstruction = true;
};

