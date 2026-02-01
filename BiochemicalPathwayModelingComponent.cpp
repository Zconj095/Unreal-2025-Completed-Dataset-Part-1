#include "BiochemicalPathwayModelingComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalPathwayModelingComponent::UBiochemicalPathwayModelingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiochemicalPathwayModelingComponent::BeginPlay()
{
	Super::BeginPlay();

	ReactionVelocity = CalculateReactionRate(Vmax, Km, SubstrateConcentration, MagicalEnergy);
	UE_LOG(LogTemp, Log, TEXT("Reaction Velocity (v): %0.4f"), ReactionVelocity);
	UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder - Reaction Velocity: %0.4f"), ReactionVelocity);
}

float UBiochemicalPathwayModelingComponent::CalculateReactionRate(float VmaxValue, float KmValue, float SubstrateValue, float MagicalEnergyValue) const
{
	const float Denominator = KmValue + SubstrateValue;
	if (FMath::IsNearlyZero(Denominator))
	{
		UE_LOG(LogTemp, Warning, TEXT("Km + [S] is zero; returning magical energy as rate."));
		return MagicalEnergyValue;
	}
	return (VmaxValue * SubstrateValue) / Denominator + MagicalEnergyValue;
}
