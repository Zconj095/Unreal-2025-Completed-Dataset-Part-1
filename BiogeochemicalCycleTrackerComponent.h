#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiogeochemicalCycleTrackerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiogeochemicalCycleTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiogeochemicalCycleTrackerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Start time for nutrient flow integration. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biogeochemical Cycle")
	float StartTime = 0.0f;

	/** End time for integration. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biogeochemical Cycle")
	float EndTime = 10.0f;

	/** Number of intervals for the trapezoidal rule. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biogeochemical Cycle", meta = (ClampMin = "1"))
	int32 NumIntervals = 1000;

	/** Computed total nutrient flow (R). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biogeochemical Cycle")
	float TotalFlow = 0.0f;

	/** Evaluates the concentration function C(t). */
	UFUNCTION(BlueprintCallable, Category = "Biogeochemical Cycle")
	float EvaluateConcentration(float TimeSeconds) const;

	/** Integrates C(t) from StartTime to EndTime using trapezoids. */
	UFUNCTION(BlueprintCallable, Category = "Biogeochemical Cycle")
	float CalculateTotalNutrientFlow() const;
};
