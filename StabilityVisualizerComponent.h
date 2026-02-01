#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StabilityVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStabilityVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStabilityVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Stability")
    int32 GridSize = 10;

    UPROPERTY(EditAnywhere, Category="Stability")
    float Dx = 0.1f;

    UPROPERTY(EditAnywhere, Category="Stability")
    float VolumeScaling = 1.0f;

    UPROPERTY(EditAnywhere, Category="Stability")
    float AmplitudeScale = 1.0f;

    UPROPERTY(EditAnywhere, Category="Stability")
    TSubclassOf<AActor> GradientActorClass;

    void GenerateWaveFunction(TArray<FVector>& OutWave) const;
    void ComputeGradients(const TArray<FVector>& Wave, TArray<FVector>& OutGradients) const;
    double ComputeStabilityIndex(const TArray<FVector>& Gradients) const;
    void VisualizeGradients(const TArray<FVector>& Gradients) const;
};
