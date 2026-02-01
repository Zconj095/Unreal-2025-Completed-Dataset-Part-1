#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalOscillationPotentialComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalOscillationPotentialComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalOscillationPotentialComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Initial biochemical flux (Φ₀). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BOP")
	float InitialFlux = 1.0f;

	/** Damping coefficient (λ). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BOP")
	float DampingCoefficient = 0.1f;

	/** Oscillation frequency (ω). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BOP")
	float Frequency = 1.0f;

	/** Whether to log Φb each tick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BOP")
	bool bLogPotential = true;

	/** Current oscillation potential. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BOP")
	float OscillationPotential = 0.0f;

	/** Returns Φb(t) = Φ₀ * exp(-λ t) * cos(ω t). */
	UFUNCTION(BlueprintCallable, Category = "BOP")
	float CalculateBOP(float Flux, float Damping, float W, float TimeSeconds) const;
};
