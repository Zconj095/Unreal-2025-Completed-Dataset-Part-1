#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralAnalysisVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralAnalysisVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralAnalysisVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Visualization")
    TSubclassOf<AActor> StressIndicatorClass;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float ForceStart = 500.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float ForceEnd = 2000.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float ForceStep = 500.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float AreaStart = 10.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float AreaEnd = 100.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float AreaStep = 10.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float StressScaleFactor = 0.02f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float HeightScale = 0.1f;

    double CalculateStress(double Force, double Area) const;
    void SpawnIndicator(float Force, double Stress, float Area) const;
    FLinearColor StressColor(double Stress) const;
};
