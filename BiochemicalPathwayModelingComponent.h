#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalPathwayModelingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalPathwayModelingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalPathwayModelingComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Vmax: Maximum reaction rate. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Pathway")
	float Vmax = 10.0f;

	/** Km: Michaelis constant. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Pathway")
	float Km = 5.0f;

	/** [S]: Substrate concentration. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Pathway")
	float SubstrateConcentration = 2.0f;

	/** μΦ: Magical energy contribution. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Pathway")
	float MagicalEnergy = 1.0f;

	/** Reaction velocity result. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Pathway")
	float ReactionVelocity = 0.0f;

	/** Computes v = (Vmax * [S]) / (Km + [S]) + μΦ. */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Pathway")
	float CalculateReactionRate(float VmaxValue, float KmValue, float SubstrateValue, float MagicalEnergyValue) const;
};
