#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveControlRateComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveControlRateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveControlRateComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** R_0: The initial adaptation rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Control")
	float InitialAdaptationRate = 1.0f;

	/** λ: The decay constant (per second). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Control")
	float DecayConstant = 0.1f;

	/** μΦ: Magical energy contribution to the rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Control")
	float MagicalEnergyContribution = 0.5f;

	/** t: Time in seconds at which we evaluate the adaptation rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Control")
	float TimeSeconds = 5.0f;

	/** Ra: The resulting adaptive control rate after the calculation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Adaptive Control")
	float AdaptiveControlRate = 0.0f;

	/** Calculates Ra = R0 * exp(-λt) + μΦ using the exposed parameters. */
	UFUNCTION(BlueprintCallable, Category = "Adaptive Control")
	float CalculateAdaptiveControlRate() const;

	/** Logs a placeholder TensorFlow validation using the same formula. */
	UFUNCTION(BlueprintCallable, Category = "Adaptive Control")
	void RunTensorFlowPlaceholder() const;
};
