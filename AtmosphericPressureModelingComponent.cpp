#include "AtmosphericPressureModelingComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAtmosphericPressureModelingComponent::UAtmosphericPressureModelingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtmosphericPressureModelingComponent::BeginPlay()
{
	Super::BeginPlay();

	PressureForce = CalculatePressureForce(PressureGradient, AirDensity);
	UE_LOG(LogTemp, Log, TEXT("Pressure Gradient Force (Fp): X=%0.3f Y=%0.3f"), PressureForce.X, PressureForce.Y);

	LogNeuralNetworkPlaceholder();
	LogTensorFlowPlaceholder();
}

FVector2D UAtmosphericPressureModelingComponent::CalculatePressureForce(const FVector2D& Gradient, float Density) const
{
	if (FMath::IsNearlyZero(Density))
	{
		UE_LOG(LogTemp, Warning, TEXT("Air density (ρ) cannot be zero."));
		return FVector2D::ZeroVector;
	}

	const FVector2D Inverse = -Gradient / Density;
	return Inverse;
}

void UAtmosphericPressureModelingComponent::LogNeuralNetworkPlaceholder() const
{
	const float GradientMagnitude = PressureGradient.Size();
	const FVector2D Prediction = CalculatePressureForce(PressureGradient, AirDensity);
	UE_LOG(LogTemp, Log, TEXT("Mock NN input (ρ=%0.3f, |∇P|=%0.3f) -> Predicted Force Magnitude=%0.3f"),
		AirDensity, GradientMagnitude, Prediction.Size());
}

void UAtmosphericPressureModelingComponent::LogTensorFlowPlaceholder() const
{
	const FVector2D Force = CalculatePressureForce(PressureGradient, AirDensity);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder: |Fp| = %0.3f"), Force.Size());
}
