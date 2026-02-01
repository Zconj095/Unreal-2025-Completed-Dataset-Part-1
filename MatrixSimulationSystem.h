#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationSystem.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationSystem : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationSystem();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float SimulationInterval = 5.f; // seconds between updates

private:
    struct FUserState
    {
        FString UserID;
        bool bIsInSimulation = false;
        float FrequencyChannel = 0.f;

        FUserState() = default;
        explicit FUserState(const FString& InUserID)
            : UserID(InUserID)
        {}

        void EnterSimulation(float Frequency)
        {
            bIsInSimulation = true;
            FrequencyChannel = Frequency;
            UE_LOG(LogTemp, Log, TEXT("User '%s' entered simulation at frequency %.2f Hz."), *UserID, Frequency);
        }

        void ExitSimulation()
        {
            bIsInSimulation = false;
            FrequencyChannel = 0.f;
            UE_LOG(LogTemp, Log, TEXT("User '%s' exited the simulation."), *UserID);
        }
    };

    void SimulateSoundWaveEffects(float Frequency);
    float CalculateChemicalEffect(float Frequency) const;
    void ApplyCountermeasure(FUserState& User, float Frequency);

    // State
    FUserState UserState;

    // Timer
    float Timer = 0.f;
};

