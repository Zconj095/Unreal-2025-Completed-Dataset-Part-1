#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymbolicParserComponent.h"
#include "SymbolProcessingVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymbolProcessingVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymbolProcessingVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Symbol Visualization")
    TSubclassOf<AActor> PointActorClass;

    UPROPERTY(EditAnywhere, Category="Symbol Visualization")
    TArray<double> Tokens = { 2.0, 3.14159, 1.0 };

    UPROPERTY(EditAnywhere, Category="Symbol Visualization")
    TArray<double> Weights = { 0.5, 1.0, 1.5 };

    UPROPERTY(EditAnywhere, Category="Symbol Visualization")
    TArray<ESymbolicTransformType> Transforms = {
        ESymbolicTransformType::Square,
        ESymbolicTransformType::Sine,
        ESymbolicTransformType::Logarithm
    };

    void SpawnPoint(double Value) const;
    static double ApplyTransform(ESymbolicTransformType Type, double Value);
};
