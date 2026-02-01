#include "ClimateInteractionComponent.h"

UClimateInteractionComponent::UClimateInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UClimateInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	Temperature = CalculateTemperatureAtTime(AccumulatedDays);
	UE_LOG(LogTemp, Log, TEXT("Initial temperature: %.4f"), Temperature);
}

void UClimateInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	constexpr float SecondsPerDay = 86400.0f;
	AccumulatedDays += DeltaTime / SecondsPerDay;
	Temperature = CalculateTemperatureAtTime(AccumulatedDays);
	UE_LOG(LogTemp, Log, TEXT("Temperature at day %.2f: %.4f"), AccumulatedDays, Temperature);
}

float UClimateInteractionComponent::CalculateTemperatureAtTime(float TimeDays) const
{
	const float SpatialTerm = FMath::Cos((2.0f * PI * Location) / SpatialPeriod);
	const float TemporalTerm = FMath::Sin((2.0f * PI * TimeDays) / TemporalPeriod);
	return AverageTemperature + Amplitude * SpatialTerm * TemporalTerm;
}
