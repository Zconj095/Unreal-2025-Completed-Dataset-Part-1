#include "CellularEnergyProductionComponent.h"

#include "GameFramework/Actor.h"

UCellularEnergyProductionComponent::UCellularEnergyProductionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCellularEnergyProductionComponent::BeginPlay()
{
	Super::BeginPlay();

	ATPProductionRate = CalculateATPProduction();
	UE_LOG(LogTemp, Log, TEXT("ATP Production Rate (v): %.4f"), ATPProductionRate);
}

double UCellularEnergyProductionComponent::CalculateATPProduction() const
{
	const double Numerator = static_cast<double>(Vmax) * ADP * Pi;
	const double Denominator = (K_ADP * K_Pi) + (ADP * Pi) + MagicalEnergy;
	if (FMath::IsNearlyZero(Denominator))
	{
		UE_LOG(LogTemp, Warning, TEXT("ATP production denominator is near zero."));
		return 0.0;
	}

	return Numerator / Denominator;
}
