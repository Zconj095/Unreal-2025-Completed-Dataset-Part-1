#include "BrainEvolutionComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

namespace
{
	float ReLU(float Value)
	{
		return FMath::Max(0.0f, Value);
	}
}

UBrainEvolutionComponent::UBrainEvolutionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBrainEvolutionComponent::BeginPlay()
{
	Super::BeginPlay();

	const int32 NodeCount = FMath::Max(NumNodes, 1);
	const int32 FeatureCount = FMath::Max(FeatureSize, 1);

	const int32 MatrixSize = NodeCount * NodeCount;
	auto EnsureArray = [](TArray<float>& Array, int32 DesiredLength)
	{
		if (Array.Num() != DesiredLength)
		{
			Array.SetNumZeroed(DesiredLength);
			for (int32 Index = 0; Index < DesiredLength; ++Index)
			{
				Array[Index] = FMath::FRand();
			}
		}
	};

	EnsureArray(AdjacencyMatrix, MatrixSize);
	EnsureArray(InitialFeatures, NodeCount * FeatureCount);
	EnsureArray(WeightMatrix1, FeatureCount * FeatureCount);
	EnsureArray(WeightMatrix2, FeatureCount * FeatureCount);

	const TArray<float> Output = ComputeGNN();
	FString Result = TEXT("Final Brain Embeddings (H_final): ");
	for (float Value : Output)
	{
		Result += FString::Printf(TEXT("%0.4f "), Value);
	}
	UE_LOG(LogTemp, Log, TEXT("%s"), *Result);
}

TArray<float> UBrainEvolutionComponent::ComputeGNN() const
{
	const int32 NodeCount = FMath::Max(NumNodes, 1);
	const int32 FeatureCount = FMath::Max(FeatureSize, 1);

	auto GetMatrixValue = [](const TArray<float>& Matrix, int32 Row, int32 Col, int32 Stride) -> float
	{
		const int32 Index = Row * Stride + Col;
		return Matrix.IsValidIndex(Index) ? Matrix[Index] : 0.0f;
	};

	TArray<float> A_H0;
	A_H0.SetNumZeroed(NodeCount * FeatureCount);
	for (int32 Node = 0; Node < NodeCount; ++Node)
	{
		for (int32 Feature = 0; Feature < FeatureCount; ++Feature)
		{
			float Sum = 0.0f;
			for (int32 K = 0; K < NodeCount; ++K)
			{
				Sum += GetMatrixValue(AdjacencyMatrix, Node, K, NodeCount) *
					GetMatrixValue(InitialFeatures, K, Feature, FeatureCount);
			}
			A_H0[Node * FeatureCount + Feature] = Sum;
		}
	}

	TArray<float> H1;
	H1.SetNumZeroed(NodeCount * FeatureCount);
	for (int32 Node = 0; Node < NodeCount; ++Node)
	{
		for (int32 Feature = 0; Feature < FeatureCount; ++Feature)
		{
			float Weighted = 0.0f;
			for (int32 Index = 0; Index < FeatureCount; ++Index)
			{
				Weighted += A_H0[Node * FeatureCount + Index] *
					GetMatrixValue(WeightMatrix1, Index, Feature, FeatureCount);
			}
			H1[Node * FeatureCount + Feature] = ReLU(Weighted);
		}
	}

	TArray<float> H2;
	H2.SetNumZeroed(NodeCount * FeatureCount);
	for (int32 Node = 0; Node < NodeCount; ++Node)
	{
		for (int32 Feature = 0; Feature < FeatureCount; ++Feature)
		{
			float Weighted = 0.0f;
			for (int32 Index = 0; Index < FeatureCount; ++Index)
			{
				Weighted += H1[Node * FeatureCount + Index] *
					GetMatrixValue(WeightMatrix2, Index, Feature, FeatureCount);
			}
			H2[Node * FeatureCount + Feature] = ReLU(Weighted);
		}
	}

	return H2;
}
