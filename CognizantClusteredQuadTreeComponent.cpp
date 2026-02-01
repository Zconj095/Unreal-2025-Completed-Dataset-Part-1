// Converted from Unity CognizantClusteredQuadTree to Unreal ActorComponent.
#include "CognizantClusteredQuadTreeComponent.h"

#include "Containers/UnrealString.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

bool FCognizantQuadTreeNode::Contains(const FVector2D& Point) const
{
    return Bounds.IsInside(Point);
}

void FCognizantQuadTreeNode::Subdivide()
{
    const FVector2D Center = Bounds.GetCenter();
    const FVector2D Extent = Bounds.GetExtent() * 0.5f;

    Children[0] = MakeUnique<FCognizantQuadTreeNode>(FBox2D(Center - Extent, Center), Capacity); // Bottom-left
    Children[1] = MakeUnique<FCognizantQuadTreeNode>(FBox2D(FVector2D(Center.X, Bounds.Min.Y), FVector2D(Bounds.Max.X, Center.Y)), Capacity); // Bottom-right
    Children[2] = MakeUnique<FCognizantQuadTreeNode>(FBox2D(FVector2D(Bounds.Min.X, Center.Y), FVector2D(Center.X, Bounds.Max.Y)), Capacity); // Top-left
    Children[3] = MakeUnique<FCognizantQuadTreeNode>(FBox2D(Center, Center + Extent), Capacity); // Top-right
}

bool FCognizantQuadTreeNode::Insert(const FVector2D& Point)
{
    if (!Contains(Point))
    {
        return false;
    }

    if (Points.Num() < Capacity && !Children[0])
    {
        Points.Add(Point);
        return true;
    }

    if (!Children[0])
    {
        Subdivide();
    }

    for (int32 ChildIndex = 0; ChildIndex < 4; ++ChildIndex)
    {
        if (Children[ChildIndex]->Insert(Point))
        {
            return true;
        }
    }

    return false;
}

void FCognizantQuadTreeNode::Query(const FBox2D& Region, TArray<FVector2D>& OutPoints) const
{
    if (!Bounds.Intersect(Region))
    {
        return;
    }

    for (const FVector2D& Point : Points)
    {
        if (Region.IsInside(Point))
        {
            OutPoints.Add(Point);
        }
    }

    for (int32 ChildIndex = 0; ChildIndex < 4; ++ChildIndex)
    {
        if (Children[ChildIndex])
        {
            Children[ChildIndex]->Query(Region, OutPoints);
        }
    }
}

UCognizantClusteredQuadTreeComponent::UCognizantClusteredQuadTreeComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCognizantClusteredQuadTreeComponent::BeginPlay()
{
    Super::BeginPlay();

    NeuralLayer = MakeUnique<FCognizantClusteredNeuralLayer>(2, 1, 0.1f);
    InitializeQuadTree();
    PopulateSamplePoints();
    InsertSamplePoints();

    if (SamplePoints.Num() > 0)
    {
        TrainPoint(SamplePoints[0], 1.0f);
    }
}

void UCognizantClusteredQuadTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    PerformQuery();
}

void UCognizantClusteredQuadTreeComponent::InitializeQuadTree()
{
    const FBox2D Bounds(FVector2D::ZeroVector, BoundsSize);
    RootNode = MakeUnique<FCognizantQuadTreeNode>(Bounds, NodeCapacity);
}

void UCognizantClusteredQuadTreeComponent::PopulateSamplePoints()
{
    SamplePoints.Empty();
    SamplePoints.Add(FVector2D(10, 20));
    SamplePoints.Add(FVector2D(15, 25));
    SamplePoints.Add(FVector2D(50, 60));
    SamplePoints.Add(FVector2D(80, 85));
}

void UCognizantClusteredQuadTreeComponent::InsertSamplePoints()
{
    if (!RootNode)
    {
        return;
    }

    for (const FVector2D& Point : SamplePoints)
    {
        RootNode->Insert(Point);
    }
}

void UCognizantClusteredQuadTreeComponent::TrainPoint(const FVector2D& Point, float Target)
{
    if (!NeuralLayer)
    {
        return;
    }

    TArray<float> Inputs;
    Inputs.SetNumUninitialized(2);
    Inputs[0] = Point.X / NormalizationFactor;
    Inputs[1] = Point.Y / NormalizationFactor;

    const TArray<float>& Outputs = NeuralLayer->Forward(Inputs);
    TArray<float> OutputErrors;
    OutputErrors.SetNumUninitialized(1);
    OutputErrors[0] = Target - Outputs[0];
    NeuralLayer->Backward(Inputs, OutputErrors);

    UE_LOG(
        LogTemp,
        Log,
        TEXT("Trained on point (%.1f, %.1f), Output: %.4f, Error: %.4f"),
        Point.X,
        Point.Y,
        Outputs[0],
        OutputErrors[0]);
}

void UCognizantClusteredQuadTreeComponent::PerformQuery() const
{
    if (!RootNode)
    {
        return;
    }

    const FBox2D QueryRegion(FVector2D::ZeroVector, FVector2D(50, 50));
    TArray<FVector2D> FoundPoints;
    RootNode->Query(QueryRegion, FoundPoints);

    for (const FVector2D& Point : FoundPoints)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Point in query region: (%.1f, %.1f)"), Point.X, Point.Y);
    }
}
