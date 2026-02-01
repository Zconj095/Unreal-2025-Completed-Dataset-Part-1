#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveGeologicalFeedbackLoopComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveGeologicalFeedbackLoopComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveGeologicalFeedbackLoopComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Current feedback state (Fn). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Feedback")
	float CurrentFeedback = 0.0f;

	/** Observed geological phenomena (Og). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Feedback")
	float ObservedPhenomena = 0.0f;

	/** Expected geological outcome (Eg). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Feedback")
	float ExpectedOutcome = 0.0f;

	/** Adaptation rate constant (alpha). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Feedback")
	float AdaptationRate = 0.1f;

	/** Updated geological feedback (Fn+1). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Geological Feedback")
	float UpdatedFeedback = 0.0f;

	/** Calculates the next feedback state. */
	UFUNCTION(BlueprintCallable, Category = "Geological Feedback")
	float CalculateAGFL(float Fn, float Og, float Eg, float Alpha) const;
};
