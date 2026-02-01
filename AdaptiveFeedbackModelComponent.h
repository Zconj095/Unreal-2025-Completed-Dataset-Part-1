#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveFeedbackModelComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveFeedbackModelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveFeedbackModelComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** α: Growth rate for the logistic portion of the model. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback Model")
	float Alpha = 0.1f;

	/** β: Environmental interaction factor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback Model")
	float Beta = 0.05f;

	/** K: Carrying capacity for the population. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback Model")
	float CarryingCapacity = 100.0f;

	/** Simulation time step size. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback Model")
	float TimeStepSize = 1.0f;

	/** Samples of environmental pressures used during a single simulation run. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feedback Model")
	TArray<float> EnvironmentalPressures = { 0.1f, 0.2f, 0.3f, 0.2f, 0.1f };

	/** Calculates ΔP_t = αP(1-P/K) - βPΦ. */
	UFUNCTION(BlueprintCallable, Category = "Feedback Model")
	float ComputePopulationChange(float Population, float EnvironmentalPressure) const;

	/** Simulates population dynamics over the configured environmental pressures. */
	UFUNCTION(BlueprintCallable, Category = "Feedback Model")
	TArray<float> SimulatePopulation(float InitialPopulation) const;
};
