#include "BiogeochemicalCycleTrackerComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiogeochemicalCycleTrackerComponent::UBiogeochemicalCycleTrackerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiogeochemicalCycleTrackerComponent::BeginPlay()
{
	Super::BeginPlay();

	TotalFlow = CalculateTotalNutrientFlow();
	UE_LOG(LogTemp, Log, TEXT("Total Nutrient Flow (R): %0.2f"), TotalFlow);
}

float UBiogeochemicalCycleTrackerComponent::EvaluateConcentration(float TimeSeconds) const
{
	return 5.0f + 3.0f * FMath::Sin(TimeSeconds);
}

float UBiogeochemicalCycleTrackerComponent::CalculateTotalNutrientFlow() const
{
	const float IntervalWidth = (EndTime - StartTime) / FMath::Max(NumIntervals, 1);
	float Sum = 0.0f;

	for (int32 Index = 0; Index <= NumIntervals; ++Index)
	{
		const float TimePoint = StartTime + Index * IntervalWidth;
		float Weight = (Index == 0 || Index == NumIntervals) ? 0.5f : 1.0f;
		Sum += Weight * EvaluateConcentration(TimePoint);
	}

	return Sum * IntervalWidth;
}
