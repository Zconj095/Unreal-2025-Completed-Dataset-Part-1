#include "ClimateNeuralModelComponent.h"

#include "Math/UnrealMathUtility.h"

UClimateNeuralModelComponent::UClimateNeuralModelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UClimateNeuralModelComponent::BeginPlay()
{
	Super::BeginPlay();

	PredictedTemperature = PredictTemperature(LocationInput, TimeInput);
	UE_LOG(LogTemp, Log, TEXT("Predicted temperature (neural model): %.4f"), PredictedTemperature);
}

float UClimateNeuralModelComponent::PredictTemperature(float Location, float Time) const
{
	// Simplified mock neural output: blend location/time with smooth functions to emulate trained network.
	constexpr float DataScale = 0.01f;
	const float SpatialResponse = FMath::Sin(Location * DataScale);
	const float TemporalResponse = FMath::Cos(Time * DataScale);
	return 15.0f + 10.0f * (0.5f + 0.5f * SpatialResponse) * TemporalResponse;
}
