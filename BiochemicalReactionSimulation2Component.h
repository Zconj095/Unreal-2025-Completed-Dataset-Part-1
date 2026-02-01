#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalReactionSimulation2Component.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalReactionSimulation2Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalReactionSimulation2Component();

protected:
	virtual void BeginPlay() override;

public:
	/** Start time (t0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Reaction")
	float StartTime = 0.0f;

	/** End time (t). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Reaction")
	float EndTime = 1.0f;

	/** Number of integration samples. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Reaction", meta = (ClampMin = "1"))
	int32 NumSamples = 100;

	/** Computed reaction simulation potential (Pr). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Reaction")
	float ReactionSimulationPotential = 0.0f;

	/** Calculates the Hamiltonian at x,t (Ĥ). */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Reaction")
	float Hamiltonian(float X, float TimeSeconds) const;

	/** Calculates the (real-valued) wavefunction ψ(x,t). */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Reaction")
	float Wavefunction(float X, float TimeSeconds) const;

	/** Numerical integration for Pr. */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Reaction")
	float CalculateBRSP() const;
};
