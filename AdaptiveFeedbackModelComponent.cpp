#include "AdaptiveFeedbackModelComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAdaptiveFeedbackModelComponent::UAdaptiveFeedbackModelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveFeedbackModelComponent::BeginPlay()
{
	Super::BeginPlay();

	const float InitialPopulation = FMath::Clamp(CarryingCapacity * 0.5f, 0.0f, CarryingCapacity);
	const TArray<float> PopulationHistory = SimulatePopulation(InitialPopulation);

	for (int32 Index = 0; Index < PopulationHistory.Num(); ++Index)
	{
		UE_LOG(LogTemp, Log, TEXT("Time %d: Population = %0.2f"), Index, PopulationHistory[Index]);
	}
}

float UAdaptiveFeedbackModelComponent::ComputePopulationChange(float Population, float EnvironmentalPressure) const
{
	const float LogisticGrowth = Alpha * Population * (1.0f - Population / CarryingCapacity);
	const float PressureLoss = Beta * Population * EnvironmentalPressure;
	return LogisticGrowth - PressureLoss;
}

TArray<float> UAdaptiveFeedbackModelComponent::SimulatePopulation(float InitialPopulation) const
{
	TArray<float> PopulationHistory;
	PopulationHistory.Reserve(EnvironmentalPressures.Num());

	float CurrentPopulation = InitialPopulation;

	for (float Pressure : EnvironmentalPressures)
	{
		PopulationHistory.Add(CurrentPopulation);
		const float DeltaPopulation = ComputePopulationChange(CurrentPopulation, Pressure);
		CurrentPopulation += DeltaPopulation * TimeStepSize;
		CurrentPopulation = FMath::Max(CurrentPopulation, 0.0f);
	}

	return PopulationHistory;
}
