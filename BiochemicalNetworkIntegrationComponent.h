#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalNetworkIntegrationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalNetworkIntegrationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalNetworkIntegrationComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** Weights of biosynthetic pathways (k_i). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Network")
	TArray<float> Weights;

	/** Inputs from molecular structures (x_i). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Network")
	TArray<float> Inputs;

	/** Resulting biochemical network integration (I_b). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Network")
	float NetworkIntegration = 0.0f;

	/** Calculates I_b = Σ k_i * log(1 + x_i) */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Network")
	float CalculateBNI(const TArray<float>& WeightArray, const TArray<float>& InputArray) const;
};
