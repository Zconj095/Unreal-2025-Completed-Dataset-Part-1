// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClimateNeuralModelComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UClimateNeuralModelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UClimateNeuralModelComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Model")
	float LocationInput = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Model")
	float TimeInput = 120.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Neural Model")
	float PredictedTemperature = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Neural Model")
	float PredictTemperature(float Location, float Time) const;
};
