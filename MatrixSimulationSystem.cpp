#include "MatrixSimulationSystem.h"

AMatrixSimulationSystem::AMatrixSimulationSystem()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationSystem::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Simulation System Initialized."));

    // Initialize user state
    UserState = FUserState(TEXT("User1"));
}

void AMatrixSimulationSystem::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    Timer += DeltaSeconds;

    if (Timer >= SimulationInterval)
    {
        Timer = 0.f; // Reset timer for the next interval

        if (!UserState.bIsInSimulation)
        {
            // Automatically enter simulation with a random frequency
            const float Frequency = FMath::FRandRange(15.f, 250.f);
            UserState.EnterSimulation(Frequency);
            SimulateSoundWaveEffects(Frequency);
            ApplyCountermeasure(UserState, Frequency);
        }
        else
        {
            // Automatically exit simulation after processing
            UserState.ExitSimulation();
        }
    }
}

void AMatrixSimulationSystem::SimulateSoundWaveEffects(float Frequency)
{
    UE_LOG(LogTemp, Log, TEXT("Simulating effects for frequency %.2f Hz..."), Frequency);
    const float ChemicalEffect = CalculateChemicalEffect(Frequency);
    UE_LOG(LogTemp, Log, TEXT("Chemical effect level: %.2f"), ChemicalEffect);
}

float AMatrixSimulationSystem::CalculateChemicalEffect(float Frequency) const
{
    // Example formula: sin(degrees) * 100
    return FMath::Sin(FMath::DegreesToRadians(Frequency)) * 100.f;
}

void AMatrixSimulationSystem::ApplyCountermeasure(FUserState& User, float Frequency)
{
    if (Frequency > 200.f || Frequency < 20.f) // Example unsafe thresholds
    {
        UE_LOG(LogTemp, Warning, TEXT("Unsafe frequency detected for User '%s': %.2f Hz. Applying countermeasure."), *User.UserID, Frequency);
        User.ExitSimulation();
    }
}

