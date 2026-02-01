#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexahedron.generated.h"

UCLASS()
class PEKBGGAP_API AHexahedron : public AActor
{
    GENERATED_BODY()

public:
    AHexahedron();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateHexahedron();
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Prefab/Blueprint to spawn for each vertex
    UPROPERTY(EditAnywhere, Category = "Hexahedron")
    TSubclassOf<AActor> VertexActorClass;

    // Distance from center to each face center in cm (Unity radius equivalent). 100 = 1m
    UPROPERTY(EditAnywhere, Category = "Hexahedron", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "Hexahedron")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "Hexahedron")
    FLinearColor LineColor = FLinearColor::Red;

    UPROPERTY(EditAnywhere, Category = "Hexahedron", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "Hexahedron")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "Hexahedron")
    bool bRebuildOnConstruction = true;
};

