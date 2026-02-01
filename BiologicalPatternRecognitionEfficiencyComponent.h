#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiologicalPatternRecognitionEfficiencyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiologicalPatternRecognitionEfficiencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiologicalPatternRecognitionEfficiencyComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Φ: Neural firing rate during recognition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pattern Recognition")
	float NeuralFiringRate = 1.0f;

	/** T: Recognition time in milliseconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pattern Recognition")
	float RecognitionTime = 1.0f;

	/** μ: Neural metabolic cost per recognition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pattern Recognition")
	float NeuralCost = 1.0f;

	/** κ: Enhanced recognition multiplier. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pattern Recognition")
	float Kappa = 1.0f;

	/** Computed Biological Pattern Recognition Efficiency (BPRE). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pattern Recognition")
	float PatternRecognitionEfficiency = 0.0f;

	/** Calculates BPRE = (κ·Φ)/(T·μ). */
	UFUNCTION(BlueprintCallable, Category = "Pattern Recognition")
	float CalculateBPRE(float PhiValue, float TimeValue, float CostValue, float KappaValue) const;
};
