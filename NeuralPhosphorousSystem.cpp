#include "NeuralPhosphorousSystem.h"
#include "Engine/World.h"

#include "Misc/Guid.h"
#include "TimerManager.h"

ANeuralPhosphorousSystem::ANeuralPhosphorousSystem()
{
    PrimaryActorTick.bCanEverTick = false; // timers only
}

void ANeuralPhosphorousSystem::BeginPlay()
{
    Super::BeginPlay();

    InitializeFormulas();

    // Automate actions
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(RelaxationTimerHandle, this, &ANeuralPhosphorousSystem::SimulateRelaxationEffects, 20.f, true, 5.f);   // every 20s after 5s
        World->GetTimerManager().SetTimer(StabilizationTimerHandle, this, &ANeuralPhosphorousSystem::SimulateNeuralStabilization, 25.f, true, 10.f); // every 25s after 10s
        World->GetTimerManager().SetTimer(DisplayTimerHandle, this, &ANeuralPhosphorousSystem::DisplayCompoundProperties, 30.f, true, 15.f);        // every 30s after 15s
    }
}

ANeuralPhosphorousSystem::FChemicalCompound::FChemicalCompound(const FString& InFormula, float InFrequency, float InCycleRate, float InMatrixRotation)
    : CompoundID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
    , Formula(InFormula)
    , Frequency(InFrequency)
    , CycleRate(InCycleRate)
    , MatrixRotation(InMatrixRotation)
{
}

void ANeuralPhosphorousSystem::FChemicalCompound::DisplayProperties() const
{
    UE_LOG(LogTemp, Log, TEXT("Compound '%s' - ID: %s, Frequency: %.2f Hz, Cycle Rate: %.2f%%, Matrix Rotation: %.2f%%"), *Formula, *CompoundID, Frequency, CycleRate, MatrixRotation);
}

void ANeuralPhosphorousSystem::InitializeFormulas()
{
    H2Z7Formula = FChemicalCompound(TEXT("H2Z7"), 27.f, 3.36f, 67.1f);
    E46A7Formula = FChemicalCompound(TEXT("E46A7"), 42.f, 66.f, 55.f);
    UE_LOG(LogTemp, Log, TEXT("Neural Phosphorous chemical compounds initialized."));
}

void ANeuralPhosphorousSystem::SimulateSoundWaveInteraction(const FChemicalCompound& Compound)
{
    UE_LOG(LogTemp, Log, TEXT("Simulating sound wave interaction for compound '%s'..."), *Compound.Formula);
    const float EffectStrength = CalculateEffectStrength(Compound);
    UE_LOG(LogTemp, Log, TEXT("Effect Strength: %.2f"), EffectStrength);
}

float ANeuralPhosphorousSystem::CalculateEffectStrength(const FChemicalCompound& Compound) const
{
    return Compound.Frequency * (Compound.CycleRate / 100.f) * (Compound.MatrixRotation / 100.f);
}

void ANeuralPhosphorousSystem::SimulateRelaxationEffects()
{
    UE_LOG(LogTemp, Log, TEXT("Simulating relaxation effects for virtual body strain..."));
    SimulateSoundWaveInteraction(H2Z7Formula);
}

void ANeuralPhosphorousSystem::SimulateNeuralStabilization()
{
    UE_LOG(LogTemp, Log, TEXT("Simulating neural passageway stabilization..."));
    SimulateSoundWaveInteraction(E46A7Formula);
}

void ANeuralPhosphorousSystem::DisplayCompoundProperties()
{
    H2Z7Formula.DisplayProperties();
    E46A7Formula.DisplayProperties();
}

