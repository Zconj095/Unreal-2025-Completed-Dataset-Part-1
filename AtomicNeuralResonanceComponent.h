#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtomicNeuralResonanceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtomicNeuralResonanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtomicNeuralResonanceComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Baseline neural activity (N0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Resonance")
	float BaselineActivity = 1.0f;

	/** Amplitude of resonance enhancement (A). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Resonance")
	float ResonanceAmplitude = 0.5f;

	/** Frequency in Hz (fa). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Resonance")
	float Frequency = 1.0f;

	/** Whether to log each tick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Resonance")
	bool bLogActivity = true;

	/** Cached neural activity value. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Resonance")
	float NeuralActivity = 0.0f;

	/** Calculates neural activity based on time. */
	UFUNCTION(BlueprintCallable, Category = "Neural Resonance")
	float CalculateNeuralActivity(float TimeSeconds) const;

	/** Resets the internal timer. */
	UFUNCTION(BlueprintCallable, Category = "Neural Resonance")
	void ResetResonance();

private:
	float SimulationTime = 0.0f;
};
