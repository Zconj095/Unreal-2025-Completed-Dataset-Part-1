#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuantumNeuralNetworkInterfaceSystem.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AQuantumNeuralNetworkInterfaceSystem : public AActor
{
    GENERATED_BODY()

public:
    AQuantumNeuralNetworkInterfaceSystem();

    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, Category = "Quantum Vortex")
    float VortexStability = 812.f;

    UPROPERTY(EditAnywhere, Category = "Quantum Vortex")
    float Velocity = 67.8592f;

    UPROPERTY(EditAnywhere, Category = "Cooling")
    float MaxTemperature = 72000000.f; // Kelvin

    UPROPERTY(EditAnywhere, Category = "Cooling")
    float ReverseReactionSpeed = 7289762574.f; // rate

    UPROPERTY(EditAnywhere, Category = "Cooling")
    float CoolingRatio = 1228.651f; // deci-system ratio

    UPROPERTY(EditAnywhere, Category = "Sensors")
    int32 TotalSensors = 100;

private:
    struct FNeuralSensor
    {
        int32 SensorID = 0;
        bool bIsActive = false;

        FNeuralSensor() = default;
        explicit FNeuralSensor(int32 InID) : SensorID(InID) {}

        void Activate()
        {
            bIsActive = true;
            UE_LOG(LogTemp, Log, TEXT("Neural Sensor %d activated."), SensorID);
        }

        void Deactivate()
        {
            bIsActive = false;
            UE_LOG(LogTemp, Log, TEXT("Neural Sensor %d deactivated."), SensorID);
        }
    };

    // Setup
    void InitializeNeuralSensors();

    // Actions
    UFUNCTION()
    void ActivateSensors();

    UFUNCTION()
    void DeactivateSensors();

    UFUNCTION()
    void SimulateVortexEnergyControl();

    UFUNCTION()
    void SimulateCoolingSystem();

    // Helpers
    float CalculateEnergyOutput() const;
    float CalculateCoolantEfficiency() const;

    // Data
    TArray<FNeuralSensor> NeuralSensors;

    // Timers
    FTimerHandle ActivateHandle;
    FTimerHandle DeactivateHandle;
    FTimerHandle EnergyHandle;
    FTimerHandle CoolingHandle;
};

