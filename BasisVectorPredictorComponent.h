#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasisVectorPredictorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBasisVectorPredictorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBasisVectorPredictorComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Input parameter that drives the synthetic prediction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basis Prediction")
	float InputParameter = 1.0f;

	/** Predicted basis vector stored for Blueprint access. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basis Prediction")
	FVector PredictedBasisVector = FVector::ZeroVector;

	/** Predicts a basis vector using the configured input parameter. */
	UFUNCTION(BlueprintCallable, Category = "Basis Prediction")
	FVector PredictBasisVector(float InputValue) const;
};
