#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalDimensionalExpansionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalDimensionalExpansionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalDimensionalExpansionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** θ: Fantasy multiplier for dimensional cognition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BDE")
	float Theta = 1.0f;

	/** N: Total neurons engaged. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BDE")
	float NeuronCount = 1000.0f;

	/** d: Dimensionality of abstraction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BDE")
	float Dimensionality = 3.0f;

	/** C: Neural connectivity density. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BDE")
	float ConnectivityDensity = 0.5f;

	/** Whether to log the current result per tick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BDE")
	bool bLogResult = true;

	/** Computed BDE value. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BDE")
	float BDEResult = 0.0f;

	/** Computes BDE = θ * N^d * log2(1 + C) if C >= -1. */
	UFUNCTION(BlueprintCallable, Category = "BDE")
	float CalculateBDE(float ThetaValue, float NeuronCountValue, float DimensionalityValue, float ConnectivityValue) const;
};
