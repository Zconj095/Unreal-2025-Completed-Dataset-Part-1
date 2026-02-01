#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalMemoryEncoding2Component.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalMemoryEncoding2Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalMemoryEncoding2Component();

protected:
	virtual void BeginPlay() override;

public:
	/** Encoding efficiency constant (α). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory 2")
	float Alpha = 1.0f;

	/** Initial reference time (t0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory 2")
	float StartTime = 0.0f;

	/** Integration interval for numerical approximation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory 2")
	float IntegrationInterval = 0.1f;

	/** Whether to log the current memory capacity on update. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Memory 2")
	bool bLogCapacity = true;

	/** Current biochemical memory capacity (Mb). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Memory 2")
	float MemoryCapacity = 0.0f;

	/** Computes the current value of Bc(t). */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Memory 2")
	float CalculateBc(float TimeSeconds) const;

	/** Advances the numerical integral by one step using the provided Bc data. */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Memory 2")
	float UpdateMemoryCapacity(float CurrentBc);

private:
	TArray<float> HistoricalBc;
};
