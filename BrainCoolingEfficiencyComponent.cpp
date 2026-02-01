#include "BrainCoolingEfficiencyComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBrainCoolingEfficiencyComponent::UBrainCoolingEfficiencyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBrainCoolingEfficiencyComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBrainCoolingEfficiencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SurfaceArea <= 0.0f || TemperatureGradient <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Surface area and temperature gradient must be greater than zero."));
		CoolingEfficiency = 0.0f;
		return;
	}

	CoolingEfficiency = CalculateCoolingEfficiency(ThermalConductivity, WaterTemperature, SurfaceArea, TemperatureGradient);
	UE_LOG(LogTemp, Log, TEXT("Brain Cooling Efficiency (E_c): %0.4f"), CoolingEfficiency);
}

float UBrainCoolingEfficiencyComponent::CalculateCoolingEfficiency(float Conductivity, float Temperature, float Area, float Gradient) const
{
	return (Conductivity * Temperature) / (Area * Gradient);
}
