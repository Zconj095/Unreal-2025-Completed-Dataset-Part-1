// Converted from Unity MonoBehaviour BrainSimulation to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainSimulationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBrainSimulationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBrainSimulationComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Brain Simulation")
    int32 NumberOfStimuli = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Brain Simulation")
    float StimulusRange = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Brain Simulation")
    float SparsenessThreshold = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Brain Simulation")
    float DifferenceThreshold = 0.1f;

protected:
    virtual void BeginPlay() override;

private:
    TArray<float> Stimuli;
    TArray<float> EncodedStimuli;

    void GenerateStimuli();
    void EncodeStimuli();
    float GetAverageStimulus() const;
    void VisualizeStimuli() const;
};
