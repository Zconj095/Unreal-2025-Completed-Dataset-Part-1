// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoefficientPredictorComponent.generated.h"

USTRUCT(BlueprintType)
struct FCoefficientSet
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float A = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float B = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float C = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float K = 2.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCoefficientPredictorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCoefficientPredictorComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Prediction")
	float InputSize = 4.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Prediction")
	FCoefficientSet Coefficients;

	UFUNCTION(BlueprintCallable, Category="Prediction")
	void PredictCoefficients(float InSize);
};
