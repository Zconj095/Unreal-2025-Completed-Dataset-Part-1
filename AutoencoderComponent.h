// Converted from Unity MonoBehaviour Autoencoder to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AutoencoderComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAutoencoderComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAutoencoderComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Autoencoder|Architecture", meta=(ClampMin=1))
    int32 InputSize = 5;

    UPROPERTY(EditAnywhere, Category="Autoencoder|Architecture", meta=(ClampMin=1))
    int32 HiddenSize = 3;

    UPROPERTY(EditAnywhere, Category="Autoencoder|Architecture", meta=(ClampMin=1))
    int32 OutputSize = 5;

    UPROPERTY(EditAnywhere, Category="Autoencoder|Training", meta=(ClampMin=0.0f))
    float LearningRate = 0.01f;

    UPROPERTY(EditAnywhere, Category="Autoencoder|Training", meta=(ClampMin=1))
    int32 Epochs = 1000;

    TArray<float> WeightsInputToHidden;
    TArray<float> WeightsHiddenToOutput;
    TArray<float> BiasesHidden;
    TArray<float> BiasesOutput;

    TArray<TArray<float>> TrainingData;

    void InitializeTrainingData();
    void InitializeWeights();
    void PerformTraining();
    void SingleTrainingStep(const TArray<float>& InputSample);
    void ComputeForward(const TArray<float>& InputSample, TArray<float>& Hidden, TArray<float>& Output) const;
    float ApplyActivation(float Value) const;
    float ActivateDerivative(float Value) const;
    float EvaluateFitness() const;
};
