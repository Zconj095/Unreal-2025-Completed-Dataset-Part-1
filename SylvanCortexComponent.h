#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SylvanCortexComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USylvanCortexComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USylvanCortexComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Sylvan Cortex")
    int32 InputSize = 5;

    UPROPERTY(EditAnywhere, Category="Sylvan Cortex")
    int32 OutputSize = 3;

    TArray<double> Weights; // OutputSize * InputSize
    TArray<double> Bias;

    void InitializeNetwork();
    double Sigmoid(double Value) const;
    void ComputeSpellVector(TArray<double>& OutVector) const;
};
