#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoubleMerkaba.generated.h"

UCLASS()
class PEKBGGAP_API ADoubleMerkaba : public AActor
{
    GENERATED_BODY()

public:
    ADoubleMerkaba();

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void OnConstruction(const FTransform& Transform) override;
#endif

private:
    void CreateDoubleMerkaba();
    TArray<FVector> GenerateMerkabaVertices() const;
    void DrawEdges(const TArray<FVector>& Vertices);
    void ClearSpawned();

    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(Transient)
    TArray<TWeakObjectPtr<AActor>> SpawnedVertices;

public:
    // Actor class to spawn for each vertex
    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba")
    TSubclassOf<AActor> VertexActorClass;

    // Scale factor in cm (100 = 1m)
    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba", meta = (ClampMin = "0.0"))
    float Radius = 100.f;

    // Debug edge rendering
    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba")
    bool bDrawEdges = true;

    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba")
    FLinearColor LineColor = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba", meta = (ClampMin = "0.0"))
    float DebugLineDuration = 10.f; // seconds; 0 = one frame

    // Spawn behavior
    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba")
    bool bSpawnAtBeginPlay = true;

    UPROPERTY(EditAnywhere, Category = "DoubleMerkaba")
    bool bRebuildOnConstruction = true;
};

