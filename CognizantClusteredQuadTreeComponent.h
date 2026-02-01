// Converted from Unity CognizantClusteredQuadTree to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognizantClusteredNeuralLayer.h"
#include "CognizantClusteredQuadTreeComponent.generated.h"

struct FCognizantQuadTreeNode
{
    FBox2D Bounds;
    int32 Capacity = 4;
    TArray<FVector2D> Points;
    TUniquePtr<FCognizantQuadTreeNode> Children[4];

    FCognizantQuadTreeNode() = default;
    FCognizantQuadTreeNode(const FBox2D& InBounds, int32 InCapacity)
        : Bounds(InBounds)
        , Capacity(InCapacity)
    {}

    bool Insert(const FVector2D& Point);
    void Subdivide();
    void Query(const FBox2D& Region, TArray<FVector2D>& OutPoints) const;
    bool Contains(const FVector2D& Point) const;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognizantClusteredQuadTreeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCognizantClusteredQuadTreeComponent();

    /** Size of the quad tree bounds (width, height). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quad Tree")
    FVector2D BoundsSize = FVector2D(100.0f, 100.0f);

    /** Maximum number of points stored per node before subdivision. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quad Tree", meta=(ClampMin=1))
    int32 NodeCapacity = 4;

    /** Input normalization divisor (matching Unity example). */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Layer")
    float NormalizationFactor = 100.0f;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    TUniquePtr<FCognizantQuadTreeNode> RootNode;
    TUniquePtr<FCognizantClusteredNeuralLayer> NeuralLayer;
    TArray<FVector2D> SamplePoints;

    void InitializeQuadTree();
    void PopulateSamplePoints();
    void InsertSamplePoints();
    void TrainPoint(const FVector2D& Point, float Target);
    void PerformQuery() const;
};
