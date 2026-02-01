#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveNeuralPlasticityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveNeuralPlasticityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveNeuralPlasticityComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Plasticity coefficient (kappa). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float PlasticityCoefficient = 1.0f;

	/** Environmental stimuli (E). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float EnvironmentalStimuli = 5.0f;

	/** Genetic stimuli (G). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float GeneticStimuli = 3.0f;

	/** Neural plasticity result (P). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Plasticity")
	float NeuralPlasticity = 0.0f;

	/** Computes P = kappa * (E + G). */
	UFUNCTION(BlueprintCallable, Category = "Neural Plasticity")
	float CalculateNeuralPlasticity(float Kappa, float E, float G) const;
};
