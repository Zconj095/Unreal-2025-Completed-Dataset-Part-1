#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveFusionGrowthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveFusionGrowthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveFusionGrowthComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** G_0: Initial fusion growth rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fusion Growth")
	float InitialGrowthRate = 1.0f;

	/** k: Growth constant used in the exponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fusion Growth")
	float GrowthConstant = 0.1f;

	/** E1: First energy contribution to the fusion calculation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fusion Growth")
	float EnergyContribution1 = 10.0f;

	/** E2: Second energy contribution. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fusion Growth")
	float EnergyContribution2 = 5.0f;

	/** t: Time used for reference, kept for parity with the Unity version even though unused. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fusion Growth")
	float TimeSeconds = 0.0f;

	/** Computes G_f(t) = G_0 * exp(k * (E1 + E2)). */
	UFUNCTION(BlueprintCallable, Category = "Fusion Growth")
	float CalculateFusionGrowthRate() const;

	/** Logs a placeholder TensorFlow-style validation. */
	UFUNCTION(BlueprintCallable, Category = "Fusion Growth")
	void RunTensorFlowPlaceholder() const;
};
