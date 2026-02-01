#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArboricortexComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UArboricortexComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UArboricortexComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Recursion depth for fractal construction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arboricortex")
	int32 RecursionDepth = 5;

	/** Branching factor (rounded to an integer). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arboricortex", meta = (ClampMin = "1.0"))
	float BranchingFactor = 2.0f;

	/** Growth rate of the branches. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arboricortex")
	float RateOfExpansion = 150.0f;

	/** Starting offset from the owning actor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arboricortex")
	FVector StartOffset = FVector::ZeroVector;

	/** Whether to log the fractal value every tick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arboricortex")
	bool bLogFractalValue = true;

	/** Recursive fractal value for a given depth. */
	UFUNCTION(BlueprintCallable, Category = "Arboricortex")
	float TreeFractalValue(int32 Depth) const;

	/** Triggers generation with current settings. */
	UFUNCTION(BlueprintCallable, Category = "Arboricortex")
	void GenerateArboricortex();

private:
	void GenerateRecursiveBranch(const FVector& Position, int32 Depth);
	int32 GetBranchCount() const;
};
