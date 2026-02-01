#include "MatrixSimulator.h"
#include "Engine/World.h"

#include "TimerManager.h"

AMatrixSimulator::AMatrixSimulator()
{
    PrimaryActorTick.bCanEverTick = false; // Using timers only
}

void AMatrixSimulator::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("Matrix Simulator Initialized."));

    // Initialize user state
    UserState = FSimulationUserState(TEXT("User1"));

    // Automate simulation cycles (InvokeRepeating analogue)
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(EntryTimerHandle, this, &AMatrixSimulator::SimulateEntry, RepeatInterval, true, EntryInitialDelay);
        World->GetTimerManager().SetTimer(ExitTimerHandle, this, &AMatrixSimulator::SimulateExit, RepeatInterval, true, ExitInitialDelay);
    }
}

void AMatrixSimulator::SimulateSensoryFeed(const FSimulationUserState& User)
{
    if (!User.bIsSimulated)
    {
        UE_LOG(LogTemp, Warning, TEXT("User '%s' is not in simulation. Sensory feed skipped."), *User.UserID);
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Simulating sensory feed for User '%s'..."), *User.UserID);
    if (User.bIsHallucinogenicControl)
    {
        UE_LOG(LogTemp, Log, TEXT("User '%s' is under hallucinogenic control. Sensory feed intensified."), *User.UserID);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("User '%s' is in normal sensory feed simulation."), *User.UserID);
    }
}

void AMatrixSimulator::IntegrateWithEmulator(const FSimulationUserState& User)
{
    if (User.bIsSimulated)
    {
        UE_LOG(LogTemp, Log, TEXT("Integrating simulation effects with Matrix Emulator for User '%s'..."), *User.UserID);
        const float Enhanced = EnhanceEffects(User.SleepStage);
        UE_LOG(LogTemp, Log, TEXT("Enhanced effects level: %.2f"), Enhanced);
    }
}

float AMatrixSimulator::EnhanceEffects(float SleepStage) const
{
    return SleepStage * 1.5f;
}

void AMatrixSimulator::SimulateEntry()
{
    const float SleepStage = FMath::FRandRange(1.f, 4.f);
    UserState.EnterSimulation(SleepStage);
    SimulateSensoryFeed(UserState);
    IntegrateWithEmulator(UserState);
}

void AMatrixSimulator::SimulateExit()
{
    if (UserState.bIsSimulated)
    {
        UserState.ExitSimulation();
    }
}

