#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationMultiplier.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationMultiplier : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationMultiplier();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Multiplier")
    double CalculateMultiplier(double Frequency, int32 InNumericValue) const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Multiplier")
    void SimulateFrequencies();

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float SimulationInterval = 3.f; // seconds

private:
    void UpdateNumericValue();
    void UpdateFrequencies();

    // Parameters
    TArray<double> Frequencies;
    int32 NumericValue = 5;

    // Timer
    float Timer = 0.f;
};

