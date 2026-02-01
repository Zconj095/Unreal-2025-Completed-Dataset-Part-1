#include "BioevolutionaryDivergenceRatioComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBioevolutionaryDivergenceRatioComponent::UBioevolutionaryDivergenceRatioComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBioevolutionaryDivergenceRatioComponent::BeginPlay()
{
	Super::BeginPlay();

	DivergenceRatio = CalculateBDR(DeltaR, Omega, Rho);
	UE_LOG(LogTemp, Log, TEXT("Bioevolutionary Divergence Ratio (BDR): %0.4f"), DivergenceRatio);
}

float UBioevolutionaryDivergenceRatioComponent::CalculateBDR(float DeltaRValue, float OmegaValue, float RhoValue) const
{
	if (OmegaValue <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("Total cognitive energy (Ω) must be greater than zero."));
		return 0.0f;
	}

	return (DeltaRValue / OmegaValue) * RhoValue;
}
