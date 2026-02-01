#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BioevolutionaryDivergenceRatioComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBioevolutionaryDivergenceRatioComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBioevolutionaryDivergenceRatioComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** ΔR: Difference between evolutionary pathways. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bioevolutionary Divergence")
	float DeltaR = 1.0f;

	/** Ω: Total cognitive energy devoted to evolution. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bioevolutionary Divergence")
	float Omega = 1.0f;

	/** ρ: Fantasy multiplier enhancing divergence. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bioevolutionary Divergence")
	float Rho = 1.0f;

	/** Calculated divergence ratio (BDR). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bioevolutionary Divergence")
	float DivergenceRatio = 0.0f;

	/** Returns BDR = (ΔR / Ω) * ρ, guarding Ω > 0. */
	UFUNCTION(BlueprintCallable, Category = "Bioevolutionary Divergence")
	float CalculateBDR(float DeltaRValue, float OmegaValue, float RhoValue) const;
};
