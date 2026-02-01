#include "AstrologicalEnergyMappingComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAstrologicalEnergyMappingComponent::UAstrologicalEnergyMappingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAstrologicalEnergyMappingComponent::BeginPlay()
{
	Super::BeginPlay();

	TotalEnergyInfluence = CalculateAstrologicalEnergy();
	UE_LOG(LogTemp, Log, TEXT("Total Astrological Energy Influence (E_A): %0.4f"), TotalEnergyInfluence);

	LogNeuralNetworkPlaceholder();
	LogTensorFlowPlaceholder();
}

float UAstrologicalEnergyMappingComponent::CalculateAstrologicalEnergy() const
{
	return CalculateEnergy(GalacticMagnitudes, CelestialDistances);
}

float UAstrologicalEnergyMappingComponent::CalculateEnergy(const TArray<float>& Magnitudes, const TArray<float>& Distances) const
{
	if (Magnitudes.Num() != Distances.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Magnitudes and distances arrays must match in length."));
		return 0.0f;
	}

	float TotalEnergy = 0.0f;
	for (int32 Index = 0; Index < Magnitudes.Num(); ++Index)
	{
		const float Distance = Distances[Index];
		if (FMath::IsNearlyZero(Distance))
		{
			UE_LOG(LogTemp, Warning, TEXT("Distance for index %d is zero; skip contribution."), Index);
			return 0.0f;
		}

		TotalEnergy += Magnitudes[Index] / FMath::Square(Distance);
	}

	return TotalEnergy;
}

TArray<float> UAstrologicalEnergyMappingComponent::BuildFlattenedInput() const
{
	TArray<float> Flattened;
	Flattened.Reserve(GalacticMagnitudes.Num() + CelestialDistances.Num());
	Flattened.Append(GalacticMagnitudes);
	Flattened.Append(CelestialDistances);
	return Flattened;
}

void UAstrologicalEnergyMappingComponent::LogNeuralNetworkPlaceholder() const
{
	const TArray<float> Input = BuildFlattenedInput();
	const float Predicted = CalculateEnergy(GalacticMagnitudes, CelestialDistances);
	FString InputString = TEXT("[");
	for (int32 Index = 0; Index < Input.Num(); ++Index)
	{
		InputString += FString::Printf(TEXT("%0.1f"), Input[Index]);
		if (Index < Input.Num() - 1)
		{
			InputString += TEXT(", ");
		}
	}
	InputString += TEXT("]");

	UE_LOG(LogTemp, Log, TEXT("Mock NN input %s -> Predicted Constant: %0.4f"), *InputString, Predicted);
}

void UAstrologicalEnergyMappingComponent::LogTensorFlowPlaceholder() const
{
	const float TensorValue = CalculateEnergy(GalacticMagnitudes, CelestialDistances);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder Computation: sum(alpha_i / d_i^2) = %0.4f"), TensorValue);
}
