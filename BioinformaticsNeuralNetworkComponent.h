#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BioinformaticsNeuralNetworkComponent.generated.h"

UENUM(BlueprintType)
enum class EBioinformaticsActivationFunction : uint8
{
	Sigmoid,
	ReLU
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBioinformaticsNeuralNetworkComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBioinformaticsNeuralNetworkComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Network")
	int32 NumberOfInputs = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Network")
	TArray<float> Weights;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Network")
	TArray<float> Inputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Network")
	float Bias = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Network")
	EBioinformaticsActivationFunction ActivationFunction = EBioinformaticsActivationFunction::ReLU;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Network")
	float NeuronOutput = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Neural Network")
	float CalculateNeuronOutput() const;

private:
	float ApplyActivation(float Value) const;
};
