#include "QuantumNeuralNetworkInterfaceSystem.h"
#include "Engine/World.h"

#include "TimerManager.h"

AQuantumNeuralNetworkInterfaceSystem::AQuantumNeuralNetworkInterfaceSystem()
{
    PrimaryActorTick.bCanEverTick = false; // using timers only
}

void AQuantumNeuralNetworkInterfaceSystem::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("Quantum Neural Network Interface System Initialized."));

    InitializeNeuralSensors();

    if (UWorld* World = GetWorld())
    {
        // Automate actions (Unity InvokeRepeating equivalents)
        World->GetTimerManager().SetTimer(ActivateHandle, this, &AQuantumNeuralNetworkInterfaceSystem::ActivateSensors, 30.f, true, 2.f);
        World->GetTimerManager().SetTimer(DeactivateHandle, this, &AQuantumNeuralNetworkInterfaceSystem::DeactivateSensors, 30.f, true, 5.f);
        World->GetTimerManager().SetTimer(EnergyHandle, this, &AQuantumNeuralNetworkInterfaceSystem::SimulateVortexEnergyControl, 40.f, true, 10.f);
        World->GetTimerManager().SetTimer(CoolingHandle, this, &AQuantumNeuralNetworkInterfaceSystem::SimulateCoolingSystem, 45.f, true, 15.f);
    }
}

void AQuantumNeuralNetworkInterfaceSystem::InitializeNeuralSensors()
{
    NeuralSensors.Empty();
    NeuralSensors.Reserve(TotalSensors);
    for (int32 i = 0; i < TotalSensors; ++i)
    {
        NeuralSensors.Emplace(i + 1);
    }
    UE_LOG(LogTemp, Log, TEXT("Initialized %d neural sensors."), TotalSensors);
}

void AQuantumNeuralNetworkInterfaceSystem::ActivateSensors()
{
    for (FNeuralSensor& Sensor : NeuralSensors)
    {
        Sensor.Activate();
    }
    UE_LOG(LogTemp, Log, TEXT("All neural sensors activated."));
}

void AQuantumNeuralNetworkInterfaceSystem::DeactivateSensors()
{
    for (FNeuralSensor& Sensor : NeuralSensors)
    {
        Sensor.Deactivate();
    }
    UE_LOG(LogTemp, Log, TEXT("All neural sensors deactivated."));
}

void AQuantumNeuralNetworkInterfaceSystem::SimulateVortexEnergyControl()
{
    UE_LOG(LogTemp, Log, TEXT("Simulating vortex energy control..."));
    const float EnergyOutput = CalculateEnergyOutput();
    UE_LOG(LogTemp, Log, TEXT("Energy Output: %.6f"), EnergyOutput);
}

float AQuantumNeuralNetworkInterfaceSystem::CalculateEnergyOutput() const
{
    // Using an approximation constant as per Unity code (2.71865372^2)
    const float EApproxSquared = FMath::Pow(2.71865372f, 2.f);
    return VortexStability * EApproxSquared * Velocity;
}

void AQuantumNeuralNetworkInterfaceSystem::SimulateCoolingSystem()
{
    UE_LOG(LogTemp, Log, TEXT("Simulating deci-conductor cooling system..."));
    const float Efficiency = CalculateCoolantEfficiency();
    UE_LOG(LogTemp, Log, TEXT("Coolant Efficiency: %.6f%%"), Efficiency);
}

float AQuantumNeuralNetworkInterfaceSystem::CalculateCoolantEfficiency() const
{
    return CoolingRatio * MaxTemperature / ReverseReactionSpeed;
}

