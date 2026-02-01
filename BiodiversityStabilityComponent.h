#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiodiversityStabilityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiodiversityStabilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiodiversityStabilityComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Number of species contributing to richness. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biodiversity")
	float SpeciesRichness = 50.0f;

	/** Average interaction strength between species. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biodiversity")
	float InteractionStrength = 0.7f;

	/** Ecosystem constant (α). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biodiversity")
	float Alpha = 1.2f;

	/** Interaction weight constant (β). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biodiversity")
	float Beta = 0.8f;

	/** Calculated ecosystem stability. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biodiversity")
	float Stability = 0.0f;

	/** Rebuilds the stability calculation. */
	UFUNCTION(BlueprintCallable, Category = "Biodiversity")
	float CalculateStability(float Richness, float Interaction, float AlphaValue, float BetaValue);
};
