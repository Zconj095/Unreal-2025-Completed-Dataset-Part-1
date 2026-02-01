#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalReactionSimulationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalReactionSimulationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalReactionSimulationComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Start time (t0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Reaction")
	float StartTime = 0.0f;

	/** End time (t). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Reaction")
	float EndTime = 1.0f;

	/** Number of samples for the integral. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Reaction", meta = (ClampMin = "1"))
	int32 NumSamples = 100;

	/** Computed reaction simulation potential. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Reaction")
	float ReactionSimulationPotential = 0.0f;

	/** Simply return x² + t². */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Reaction")
	float Hamiltonian(float X, float TimeSeconds) const;

	/** Gaussian wave packet ψ(x, t). */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Reaction")
	float Wavefunction(float X, float TimeSeconds) const;

	/** Integrates the BRS potential. */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Reaction")
	float CalculateBRSP() const;
};
