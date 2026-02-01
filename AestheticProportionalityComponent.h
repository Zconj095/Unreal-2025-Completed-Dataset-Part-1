#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AestheticProportionalityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAestheticProportionalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAestheticProportionalityComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Dimension a used for the R = a / b ratio. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aesthetic")
	float DimensionA = 100.0f;

	/** Dimension b used for the R = a / b ratio. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aesthetic")
	float DimensionB = 62.0f;

	/** Acceptable tolerance when comparing to the golden ratio. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aesthetic")
	float GoldenRatioTolerance = 0.01f;

	/** Resulting proportionality ratio (R = a / b). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aesthetic")
	float ProportionalityRatio = 0.0f;

	/** Calculates R = a / b but protects against division by zero. */
	UFUNCTION(BlueprintCallable, Category = "Aesthetic")
	float CalculateProportionality(float A, float B) const;

	/** Checks whether a ratio lies within the configured tolerance of the golden ratio. */
	UFUNCTION(BlueprintCallable, Category = "Aesthetic")
	bool IsCloseToGoldenRatio(float Ratio, float Tolerance) const;

	/** Logs a stub neural network prediction for the configured dimensions. */
	UFUNCTION(BlueprintCallable, Category = "Aesthetic")
	void LogNeuralNetworkPrediction() const;

	/** Logs a stub TensorFlow-style computation for the configured dimensions. */
	UFUNCTION(BlueprintCallable, Category = "Aesthetic")
	void LogTensorFlowComputation() const;
};
