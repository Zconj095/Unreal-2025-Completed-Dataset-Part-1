// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMNeuralPlasticityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCMNeuralPlasticityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCMNeuralPlasticityComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Plasticity")
	float PlasticityCoefficient = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Plasticity")
	float CelestialStimuli = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Plasticity")
	float LuminosityStimuli = 0.2f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Neural Plasticity")
	float NeuralPlasticity = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Neural Plasticity")
	void UpdateStimuli(float NewCelestial, float NewLuminosity);
};
