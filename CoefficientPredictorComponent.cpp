#include "CoefficientPredictorComponent.h"

#include "Math/UnrealMathUtility.h"

UCoefficientPredictorComponent::UCoefficientPredictorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCoefficientPredictorComponent::BeginPlay()
{
	Super::BeginPlay();
	PredictCoefficients(InputSize);
}

void UCoefficientPredictorComponent::PredictCoefficients(float InSize)
{
	InputSize = InSize;

	// Simplified coefficient prediction heuristic
	Coefficients.A = 1.0f + 0.1f * InSize;
	Coefficients.B = 2.0f - 0.05f * InSize;
	Coefficients.C = 5.0f - 0.1f * InSize;
	Coefficients.K = 2.0f + 0.05f * InSize;

	UE_LOG(LogTemp, Log, TEXT("Predicted coefficients (a=%.2f, b=%.2f, c=%.2f, k=%.2f)"), Coefficients.A, Coefficients.B, Coefficients.C, Coefficients.K);
}
