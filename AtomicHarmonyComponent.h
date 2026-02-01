#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtomicHarmonyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtomicHarmonyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtomicHarmonyComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Baseline atomic harmony (H0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Harmony")
	float BaselineHarmony = 1.0f;

	/** Sensitivity to synchronization (gamma). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Harmony")
	float Sensitivity = 0.5f;

	/** Frequency of interactions (fa, Hz). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Harmony")
	float InteractionFrequency = 2.0f;

	/** Whether to log the harmony value each tick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Harmony")
	bool bLogHarmony = true;

	/** Current computed harmony value (Ha). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Atomic Harmony")
	float AtomicHarmony = 0.0f;

	/** Calculates Ha = H0 * (1 + gamma * sin(2πfa t)). */
	UFUNCTION(BlueprintCallable, Category = "Atomic Harmony")
	float CalculateAtomicHarmony(float TimeSeconds) const;

	/** Resets the internal time accumulator. */
	UFUNCTION(BlueprintCallable, Category = "Atomic Harmony")
	void ResetHarmonyTime();

private:
	float SimulationTime = 0.0f;
};
