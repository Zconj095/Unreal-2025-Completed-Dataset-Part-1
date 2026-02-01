#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElvenMageAdaptiveNeuralPlasticityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UElvenMageAdaptiveNeuralPlasticityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UElvenMageAdaptiveNeuralPlasticityComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** α: Sensitivity to stimuli. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float Alpha = 1.5f;

	/** ΔS: Change in environmental stimuli. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float DeltaS = 2.0f;

	/** β: Sensitivity to magical energy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float Beta = 0.8f;

	/** Φ: Magical energy flow. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Plasticity")
	float Phi = 3.0f;

	/** Computed plasticity rate (P). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Plasticity")
	float PlasticityRate = 0.0f;

	/** Computes P = α * ΔS + β * Φ. */
	UFUNCTION(BlueprintCallable, Category = "Neural Plasticity")
	float CalculatePlasticityRate(float InAlpha, float InDeltaS, float InBeta, float InPhi) const;

	/** Logs a mock neural network prediction. */
	UFUNCTION(BlueprintCallable, Category = "Neural Plasticity")
	void LogNeuralNetworkPrediction() const;

	/** Logs a mock TensorFlow computation. */
	UFUNCTION(BlueprintCallable, Category = "Neural Plasticity")
	void LogTensorFlowComputation() const;
};
