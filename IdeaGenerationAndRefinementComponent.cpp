#include "IdeaGenerationAndRefinementComponent.h"
#include "Engine/Engine.h"

UIdeaGenerationAndRefinementComponent::UIdeaGenerationAndRefinementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UIdeaGenerationAndRefinementComponent::BeginPlay()
{
	Super::BeginPlay();
	RecalculateCreativePotential();
}

void UIdeaGenerationAndRefinementComponent::InitializeParameters()
{
	CreativePotential = 0.0f;
}

float UIdeaGenerationAndRefinementComponent::CalculateCreativePotential(float InConnections, float InConstraints) const
{
	if (FMath::IsNearlyZero(InConstraints))
	{
		UE_LOG(LogTemp, Error, TEXT("Logical constraints (L) cannot be zero!"));
		return 0.0f;
	}

	return InConnections / InConstraints;
}

float UIdeaGenerationAndRefinementComponent::PredictCreativePotentialWithMockNetwork(float InConnections, float InConstraints) const
{
	const float BaseValue = CalculateCreativePotential(InConnections, InConstraints);
	return BaseValue * 0.95f; // Mock neural prediction as a slight adjustment
}

float UIdeaGenerationAndRefinementComponent::ComputeCreativePotentialWithTensorFlowStub(float InConnections, float InConstraints) const
{
	if (FMath::IsNearlyZero(InConstraints))
	{
		UE_LOG(LogTemp, Error, TEXT("TensorFlow stub cannot divide by zero constraints."));
		return 0.0f;
	}

	return InConnections / InConstraints;
}

void UIdeaGenerationAndRefinementComponent::LogCreativePotential(float InCreativePotential) const
{
	UE_LOG(LogTemp, Log, TEXT("Creative Potential (I_C): %.4f"), InCreativePotential);
}

void UIdeaGenerationAndRefinementComponent::RecalculateCreativePotential()
{
	InitializeParameters();

	const float Result = CalculateCreativePotential(Connections, Constraints);
	LogCreativePotential(Result);
	CreativePotential = Result;

	const float NetworkPrediction = PredictCreativePotentialWithMockNetwork(Connections, Constraints);
	UE_LOG(LogTemp, Log, TEXT("Predicted Creative Potential (I_C): %.4f"), NetworkPrediction);

	const float TensorFlowResult = ComputeCreativePotentialWithTensorFlowStub(Connections, Constraints);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Computation Result (I_C): %.4f"), TensorFlowResult);
}
