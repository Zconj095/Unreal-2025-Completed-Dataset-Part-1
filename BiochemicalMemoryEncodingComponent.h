#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalMemoryEncodingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalMemoryEncodingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalMemoryEncodingComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Encoding efficiency constant (α). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory")
	float EncodingEfficiency = 1.0f;

	/** Start time (t₀). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory")
	float StartTime = 0.0f;

	/** End time (t). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory")
	float EndTime = 10.0f;

	/** Number of steps to use for the trapezoidal sum. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory", meta = (ClampMin = "1"))
	int32 IntegrationSteps = 1000;

	/** Last computed memory encoding value. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Memory")
	float MemoryCapacity = 0.0f;

	/** Computes complexity at time t (P_c). */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Memory")
	float BiochemicalComplexity(float TimeSeconds) const;

	/** Recomputes the memory encoding integral. */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Memory")
	float CalculateBiochemicalMemory();
};
