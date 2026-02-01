#include "BondEnergyCalculatorComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

static constexpr double PlancksConstant = 6.626e-34;
static constexpr double SpeedOfLight = 3.0e8;

UBondEnergyCalculatorComponent::UBondEnergyCalculatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBondEnergyCalculatorComponent::BeginPlay()
{
	Super::BeginPlay();

	BondEnergy = CalculateBondEnergy(Wavelength);
	if (BondEnergy <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wavelength must be greater than zero."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Bond Dissociation Energy (E_b): %0.4e J"), BondEnergy);
	}
}

float UBondEnergyCalculatorComponent::CalculateBondEnergy(float WavelengthValue) const
{
	if (WavelengthValue <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}
	return static_cast<float>((PlancksConstant * SpeedOfLight) / WavelengthValue);
}
