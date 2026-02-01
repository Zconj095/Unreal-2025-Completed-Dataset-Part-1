#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdaptiveSynergisticGrowthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAdaptiveSynergisticGrowthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdaptiveSynergisticGrowthComponent();

protected:
	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;

private:
	/** Samples of growth (one value per resolution step). */
	UPROPERTY(VisibleAnywhere, Category = "Adaptive Growth")
	TArray<float> GrowthSamples;

	void GenerateGrowthSamples();

public:
	/** G0: Initial growth constant. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth", meta = (ClampMin = "0.0"))
	float InitialGrowthRate = 1.0f;

	/** k: Growth constant applied in the exponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth")
	float GrowthConstant = 0.1f;

	/** Ebio: Biological energy contribution. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth")
	float BiologicalEnergy = 0.5f;

	/** Emagic: Magical energy contribution. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth")
	float MagicalEnergy = 0.3f;

	/** Start time of the simulation window. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth")
	float StartTime = 0.0f;

	/** End time of the simulation window. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth")
	float EndTime = 10.0f;

	/** Resolution of the sampled curve. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Adaptive Growth", meta = (ClampMin = "1"))
	int32 Resolution = 100;

	/** Calculates the growth curve. */
	UFUNCTION(BlueprintCallable, Category = "Adaptive Growth")
	const TArray<float>& CalculateSynergisticGrowth();

	/** Logs placeholder TensorFlow validation of the growth curve. */
	UFUNCTION(BlueprintCallable, Category = "Adaptive Growth")
	void LogTensorFlowValidation() const;
};
