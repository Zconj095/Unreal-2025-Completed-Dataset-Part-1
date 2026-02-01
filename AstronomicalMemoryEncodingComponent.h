#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstronomicalMemoryEncodingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAstronomicalMemoryEncodingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAstronomicalMemoryEncodingComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Encoding efficiency constant (alpha). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Astronomical Memory")
	float Alpha = 1.0f;

	/** Initial astronomical complexity (C0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Astronomical Memory")
	float InitialComplexity = 1.0f;

	/** Growth rate of complexity (ra). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Astronomical Memory")
	float GrowthRate = 0.1f;

	/** Calculated memory capacity (Ma). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Astronomical Memory")
	float MemoryCapacity = 0.0f;

	/** Computes complexity Cc(t) = C0 * exp(ra * t). */
	UFUNCTION(BlueprintCallable, Category = "Astronomical Memory")
	float CalculateAstronomicalComplexity(float TimeSeconds) const;

	/** Resets the integrated memory capacity. */
	UFUNCTION(BlueprintCallable, Category = "Astronomical Memory")
	void ResetMemory();

private:
	float PreviousComplexity = 0.0f;
	float PreviousTime = 0.0f;
};
