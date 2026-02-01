#include "BasisVectorPredictorComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBasisVectorPredictorComponent::UBasisVectorPredictorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBasisVectorPredictorComponent::BeginPlay()
{
	Super::BeginPlay();

	PredictedBasisVector = PredictBasisVector(InputParameter);
	UE_LOG(LogTemp, Log, TEXT("Predicted Basis Vector: X=%0.4f Y=%0.4f Z=%0.4f"),
		PredictedBasisVector.X, PredictedBasisVector.Y, PredictedBasisVector.Z);
}

FVector UBasisVectorPredictorComponent::PredictBasisVector(float InputValue) const
{
	const float Scaled = FMath::Clamp(InputValue, 0.0f, 2.0f);
	const float X = FMath::Sin(Scaled * PI);
	const float Y = FMath::Cos(Scaled * PI);
	const float Z = FMath::Frac(Scaled * 0.5f);
	return FVector(X, Y, Z).GetSafeNormal();
}
