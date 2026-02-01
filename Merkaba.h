#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Merkaba.generated.h"

UCLASS()
class PEKBGGAP_API AMerkaba : public AActor
{
    GENERATED_BODY()

public:
    AMerkaba();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateMerkaba();
    TArray<FVector> GenerateMerkabaVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Prefab/Blueprint to spawn for each vertex
    UPROPERTY(EditAnywhere, Category = "Merkaba")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor in cm (100 = 1m), multiplies unit vertex positions
    UPROPERTY(EditAnywhere, Category = "Merkaba", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "Merkaba")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "Merkaba")
    FLinearColor LineColor = FLinearColor(0.f, 1.f, 1.f, 1.f);

    UPROPERTY(EditAnywhere, Category = "Merkaba", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "Merkaba")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "Merkaba")
    bool bRebuildOnConstruction = true;
};
