#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NeuralPhosphorousSystem.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ANeuralPhosphorousSystem : public AActor
{
    GENERATED_BODY()

public:
    ANeuralPhosphorousSystem();

    virtual void BeginPlay() override;

private:
    struct FChemicalCompound
    {
        FString CompoundID;
        FString Formula;
        float Frequency = 0.f;
        float CycleRate = 0.f;     // percent
        float MatrixRotation = 0.f; // percent

        FChemicalCompound() = default;
        FChemicalCompound(const FString& InFormula, float InFrequency, float InCycleRate, float InMatrixRotation);

        void DisplayProperties() const;
    };

    void InitializeFormulas();
    void SimulateSoundWaveInteraction(const FChemicalCompound& Compound);
    float CalculateEffectStrength(const FChemicalCompound& Compound) const;

    UFUNCTION()
    void SimulateRelaxationEffects();

    UFUNCTION()
    void SimulateNeuralStabilization();

    UFUNCTION()
    void DisplayCompoundProperties();

    // Compounds
    FChemicalCompound H2Z7Formula;
    FChemicalCompound E46A7Formula;

    // Timers (InvokeRepeating equivalents)
    FTimerHandle RelaxationTimerHandle;
    FTimerHandle StabilizationTimerHandle;
    FTimerHandle DisplayTimerHandle;
};

