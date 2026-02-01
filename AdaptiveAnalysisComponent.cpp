#include "AdaptiveAnalysisComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAdaptiveAnalysisComponent::UAdaptiveAnalysisComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveAnalysisComponent::BeginPlay()
{
	Super::BeginPlay();

	AdaptiveAnalysisIndex = CalculateAdaptiveAnalysis(CognitiveEfficiency, AnalysisTime, ComplexityFactor);
	UE_LOG(LogTemp, Log, TEXT("Adaptive Analysis Index (A_a): %0.4f"), AdaptiveAnalysisIndex);
}

float UAdaptiveAnalysisComponent::CalculateAdaptiveAnalysis(float Psi, float Ta, float LambdaE) const
{
	const float Denominator = FMath::Max(Ta + LambdaE, KINDA_SMALL_NUMBER);
	return Psi / Denominator;
}

void UAdaptiveAnalysisComponent::PredictAdaptiveAnalysisWithMockNetwork()
{
	const struct FTrainingSample
	{
		float Psi;
		float Ta;
		float LambdaE;
		float Expected;
	};

	const TArray<FTrainingSample> TrainingSamples = {
		{80.0f, 10.0f, 5.0f, 5.33f},
		{100.0f, 12.0f, 7.0f, 5.26f},
		{90.0f, 8.0f, 6.0f, 6.0f},
	};

	for (const FTrainingSample& Sample : TrainingSamples)
	{
		const float Prediction = CalculateAdaptiveAnalysis(Sample.Psi, Sample.Ta, Sample.LambdaE);
		UE_LOG(LogTemp, Log, TEXT("Mock NN: Psi=%0.2f, T_a=%0.2f, LambdaE=%0.2f -> %0.4f (expected %0.4f)"),
			Sample.Psi, Sample.Ta, Sample.LambdaE, Prediction, Sample.Expected);
	}

	const float PredictedIndex = CalculateAdaptiveAnalysis(85.0f, 9.0f, 6.0f);
	UE_LOG(LogTemp, Log, TEXT("Predicted Adaptive Analysis Index (A_a): %0.4f"), PredictedIndex);
}

void UAdaptiveAnalysisComponent::RunTensorFlowPlaceholder()
{
	const float Sum = AnalysisTime + ComplexityFactor;
	const float TensorResult = CalculateAdaptiveAnalysis(CognitiveEfficiency, AnalysisTime, ComplexityFactor);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: Psi=%0.2f, T_a=%0.2f, LambdaE=%0.2f, A_a=%0.4f"),
		CognitiveEfficiency, AnalysisTime, ComplexityFactor, TensorResult);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: internal sum (T_a + LambdaE) = %0.2f"), Sum);
}
