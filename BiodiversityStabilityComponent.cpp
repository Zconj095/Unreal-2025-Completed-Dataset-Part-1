#include "BiodiversityStabilityComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiodiversityStabilityComponent::UBiodiversityStabilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiodiversityStabilityComponent::BeginPlay()
{
	Super::BeginPlay();

	Stability = CalculateStability(SpeciesRichness, InteractionStrength, Alpha, Beta);
	UE_LOG(LogTemp, Log, TEXT("Ecosystem Stability: %0.4f"), Stability);
}

float UBiodiversityStabilityComponent::CalculateStability(float Richness, float Interaction, float AlphaValue, float BetaValue)
{
	if (Richness <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("Species richness must be > 0."));
		return 0.0f;
	}

	return AlphaValue * FMath::Loge(Richness) + BetaValue * Interaction;
}
