#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SylvanCortexSector2Component.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USylvanCortexSector2Component : public UActorComponent
{
    GENERATED_BODY()

public:
    USylvanCortexSector2Component();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Sylvan Cortex")
    int32 InputSize = 4;

    UPROPERTY(EditAnywhere, Category="Sylvan Cortex")
    int32 OutputSize = 3;

    TArray<double> Weights;
    TArray<double> Inputs;
    TArray<double> Biases;

    void InitializeParameters();
    double Sigmoid(double Value) const;
    void ComputeSpellVector(TArray<double>& OutVector) const;
};
