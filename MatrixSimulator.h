#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulator.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulator : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulator();

    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float EntryInitialDelay = 1.f;

    UPROPERTY(EditAnywhere, Category = "Automation")
    float ExitInitialDelay = 6.f;

    UPROPERTY(EditAnywhere, Category = "Automation")
    float RepeatInterval = 10.f; // seconds

private:
    struct FSimulationUserState
    {
        FString UserID;
        bool bIsSimulated = false;
        float SleepStage = 0.f;
        bool bIsHallucinogenicControl = false;

        FSimulationUserState() = default;
        explicit FSimulationUserState(const FString& InUserID)
            : UserID(InUserID)
        {
        }

        void EnterSimulation(float InSleepStage)
        {
            bIsSimulated = true;
            SleepStage = InSleepStage;
            bIsHallucinogenicControl = (SleepStage >= 3.f);
            UE_LOG(LogTemp, Log, TEXT("User '%s' entered simulation at sleep stage %.2f."), *UserID, SleepStage);
        }

        void ExitSimulation()
        {
            bIsSimulated = false;
            SleepStage = 0.f;
            bIsHallucinogenicControl = false;
            UE_LOG(LogTemp, Log, TEXT("User '%s' exited the simulation."), *UserID);
        }
    };

    void SimulateSensoryFeed(const FSimulationUserState& User);
    void IntegrateWithEmulator(const FSimulationUserState& User);
    float EnhanceEffects(float SleepStage) const;

    UFUNCTION()
    void SimulateEntry();

    UFUNCTION()
    void SimulateExit();

    // State
    FSimulationUserState UserState;

    // Timers
    FTimerHandle EntryTimerHandle;
    FTimerHandle ExitTimerHandle;
};

