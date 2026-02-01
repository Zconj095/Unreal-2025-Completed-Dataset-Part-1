#include "AirflowDynamicsComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAirflowDynamicsComponent::UAirflowDynamicsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAirflowDynamicsComponent::BeginPlay()
{
	Super::BeginPlay();

	CalculatedConstant = CalculateBernoulliConstant(StaticPressure, AirDensity, AirflowVelocity, GravitationalAccel, Height, MagicalEnergyFlux);
	UE_LOG(LogTemp, Log, TEXT("Calculated Constant: %0.4f"), CalculatedConstant);

	LogNeuralNetworkPrediction();
	LogTensorFlowComputation();
}

float UAirflowDynamicsComponent::CalculateBernoulliConstant(float Pressure, float Density, float Velocity, float Gravity, float HeightValue, float EnergyFlux) const
{
	const float DynamicPressure = 0.5f * Density * FMath::Square(Velocity);
	const float PotentialEnergy = Density * Gravity * HeightValue;
	return Pressure + DynamicPressure + PotentialEnergy + EnergyFlux;
}

void UAirflowDynamicsComponent::LogNeuralNetworkPrediction() const
{
	const float MockPrediction = CalculateBernoulliConstant(StaticPressure, AirDensity, AirflowVelocity, GravitationalAccel, Height, MagicalEnergyFlux);
	UE_LOG(LogTemp, Log, TEXT("Mock NN Predicted Constant: %0.4f"), MockPrediction);
}

void UAirflowDynamicsComponent::LogTensorFlowComputation() const
{
	const float TensorValue = CalculateBernoulliConstant(StaticPressure, AirDensity, AirflowVelocity, GravitationalAccel, Height, MagicalEnergyFlux);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder Computation: %0.4f"), TensorValue);
}
