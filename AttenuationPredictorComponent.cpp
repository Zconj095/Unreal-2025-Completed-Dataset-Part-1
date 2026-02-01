#include "AttenuationPredictorComponent.h"
#include "Logging/LogMacros.h"

UAttenuationPredictorComponent::UAttenuationPredictorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttenuationPredictorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Simple heuristic matching the Unity sample: average ratio of intensity/distance
	for (int32 Index = 0; Index < FMath::Min(InitialIntensities.Num(), Distances.Num()); ++Index)
	{
		const float Prediction = Predict(InitialIntensities[Index], Distances[Index]);
		UE_LOG(LogTemp, Log, TEXT("Sample %d -> InitialIntensity=%0.1f, Distance=%0.1f, Attenuation=%0.4f"),
			Index + 1, InitialIntensities[Index], Distances[Index], Prediction);
		PredictedCoefficient = Prediction;
	}
}

float UAttenuationPredictorComponent::Predict(float Intensity, float Distance) const
{
	if (Distance <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}
	return (Intensity / Distance) * 0.0025f; // Scaled heuristic
}
