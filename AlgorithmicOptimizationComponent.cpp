#include "AlgorithmicOptimizationComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAlgorithmicOptimizationComponent::UAlgorithmicOptimizationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAlgorithmicOptimizationComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int32 N = 1; N <= 10; ++N)
	{
		const float Complexity = ComputeTimeComplexity(static_cast<float>(N));
		UE_LOG(LogTemp, Log, TEXT("T(%d) = %0.4f"), N, Complexity);
	}
}

float UAlgorithmicOptimizationComponent::ComputeTimeComplexity(float N) const
{
	if (N <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("ComputeTimeComplexity requires N > 0, received %0.3f"), N);
		return 0.0f;
	}

	const float SafeN = FMath::Max(N, SMALL_NUMBER);
	const float PolynomialTerm = CoefficientA * FMath::Pow(SafeN, ExponentK);
	const float LogTerm = CoefficientB * FMath::Loge(SafeN);
	return PolynomialTerm + LogTerm + ConstantC;
}
