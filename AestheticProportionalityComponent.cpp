#include "AestheticProportionalityComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

constexpr float kGoldenRatio = 1.618f;

UAestheticProportionalityComponent::UAestheticProportionalityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAestheticProportionalityComponent::BeginPlay()
{
	Super::BeginPlay();

	ProportionalityRatio = CalculateProportionality(DimensionA, DimensionB);
	UE_LOG(LogTemp, Log, TEXT("Proportionality Ratio (R): %0.4f"), ProportionalityRatio);

	if (IsCloseToGoldenRatio(ProportionalityRatio, GoldenRatioTolerance))
	{
		UE_LOG(LogTemp, Log, TEXT("The dimensions are close to the Golden Ratio."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("The dimensions deviate from the Golden Ratio."));
	}

	LogNeuralNetworkPrediction();
	LogTensorFlowComputation();
}

float UAestheticProportionalityComponent::CalculateProportionality(float A, float B) const
{
	if (FMath::IsNearlyZero(B))
	{
		UE_LOG(LogTemp, Warning, TEXT("AestheticProportionalityComponent: Dimension B cannot be zero."));
		return 0.0f;
	}

	return A / B;
}

bool UAestheticProportionalityComponent::IsCloseToGoldenRatio(float Ratio, float Tolerance) const
{
	return FMath::Abs(Ratio - kGoldenRatio) <= FMath::Abs(Tolerance);
}

void UAestheticProportionalityComponent::LogNeuralNetworkPrediction() const
{
	const float PredictedRatio = CalculateProportionality(DimensionA, DimensionB);
	UE_LOG(LogTemp, Log, TEXT("Mock NN Prediction: a=%0.2f, b=%0.2f -> R=%0.4f"), DimensionA, DimensionB, PredictedRatio);
}

void UAestheticProportionalityComponent::LogTensorFlowComputation() const
{
	const float ComputedRatio = CalculateProportionality(DimensionA, DimensionB);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: R = a / b = %0.4f"), ComputedRatio);
}
