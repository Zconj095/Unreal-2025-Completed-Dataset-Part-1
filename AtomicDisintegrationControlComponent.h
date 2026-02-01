#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtomicDisintegrationControlComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtomicDisintegrationControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtomicDisintegrationControlComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** η_p: Neural precision in atomization control. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Disintegration")
	float NeuralPrecision = 0.9f;

	/** E_i: Input energy for the disintegration process. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Disintegration")
	float InputEnergy = 50.0f;

	/** E_t: Threshold energy required for atomic disintegration. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Disintegration")
	float ThresholdEnergy = 100.0f;

	/** Calculated disintegration control capacity. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Atomic Disintegration")
	float DisintegrationControl = 0.0f;

	/** Calculates neural precision-weighted control capacity (η_p * (E_i / E_t)). */
	UFUNCTION(BlueprintCallable, Category = "Atomic Disintegration")
	float CalculateDisintegrationControl(float NeuralPrecisionValue, float InputEnergyValue, float ThresholdEnergyValue) const;
};
