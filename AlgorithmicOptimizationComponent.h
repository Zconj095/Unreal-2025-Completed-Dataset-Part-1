#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlgorithmicOptimizationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAlgorithmicOptimizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAlgorithmicOptimizationComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Coefficient multiplying n^k. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithmic Optimization")
	float CoefficientA = 1.5f;

	/** Coefficient multiplying log(n). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithmic Optimization")
	float CoefficientB = 2.0f;

	/** Constant term. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithmic Optimization")
	float ConstantC = 5.0f;

	/** Exponent applied to n. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Algorithmic Optimization")
	float ExponentK = 2.0f;

	/** Computes T(n) = a*n^k + b*log(n) + c, guards against zero input. */
	UFUNCTION(BlueprintCallable, Category = "Algorithmic Optimization")
	float ComputeTimeComplexity(float N) const;
};
