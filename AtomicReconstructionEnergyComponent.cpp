#include "AtomicReconstructionEnergyComponent.h"

UAtomicReconstructionEnergyComponent::UAtomicReconstructionEnergyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UAtomicReconstructionEnergyComponent::CalculateEnergyInput(float EnthalpyChange, float EntropyChange, float Temperature, float MagicalEnergy) const
{
	return EnthalpyChange + (EntropyChange * Temperature) + MagicalEnergy;
}
