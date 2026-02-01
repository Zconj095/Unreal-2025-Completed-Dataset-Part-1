#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveNeuralMutationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveNeuralMutationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveNeuralMutationComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Mu: Mutation constant exposed to designers. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Mutation")
	float MutationConstant = 0.1f;

	/** N: Current neural capacity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Mutation")
	float CurrentNeuralCapacity = 50.0f;

	/** K: Maximum neural mutation capacity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Mutation")
	float MaximumCapacity = 100.0f;

	/** ?N: Cached result of the mutation rate calculation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Mutation")
	float RateOfNeuralMutations = 0.0f;

	/** Calculates the rate of neural mutations using the logistic-style formula. */
	UFUNCTION(BlueprintCallable, Category = "Neural Mutation")
	float CalculateNeuralMutationRate(float Mu, float N, float K) const;
};
