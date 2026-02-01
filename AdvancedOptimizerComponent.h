// Converted from Unity MonoBehaviour to Unreal Actor Component.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedOptimizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAdvancedOptimizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAdvancedOptimizerComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization|Parameters")
    float Alpha = 0.01f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization|Parameters")
    float Beta = 0.9f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization|Parameters")
    float Rho = 0.9f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization|Parameters")
    int32 Epochs = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization|Parameters")
    int32 NumWeights = 5;

protected:
    virtual void BeginPlay() override;

private:
    TArray<float> Weights;
    TArray<float> Velocity;
    TArray<float> AccumulatedSquaredGradients;

    void InitializeWeights();
    TArray<float> ComputeGradients() const;
    void PerformOptimization();
    void LogWeights(int32 Epoch) const;
};
