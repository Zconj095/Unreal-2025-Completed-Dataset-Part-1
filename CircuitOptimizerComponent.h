// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CircuitOptimizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCircuitOptimizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCircuitOptimizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Desired flux value to hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Circuit Optimization")
	float DesiredFlux = 5.0f;

	/** Frequency in Hz */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Circuit Optimization")
	float Frequency = 60.0f;

	/** Computed optimized parameter output */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Circuit Optimization")
	float OptimizedResult = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Circuit Optimization")
	float OptimizeCircuit(float InResistance, float InCapacitance);
};
