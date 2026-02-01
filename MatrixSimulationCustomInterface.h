#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationCustomInterface.generated.h"

// Enum to represent available options
UENUM()
enum class ESimulationOption : uint8
{
    Reconnection,
    CreateSensors,
    EmotionalEditor,
    SimulationCloning,
    FrequencyControl,
    DestructionModifier,
    CreationModifier,
    CreationSystem,
    DestructionSystem,
    EditingManipulator,
    NetworkConnector,
    ServerAdjustment,
    DomainModifying,

    Count UMETA(Hidden)
};

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationCustomInterface : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationCustomInterface();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Custom Interface")
    void DisplayAllOptions() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float SettingsUpdateInterval = 5.f; // seconds

private:
    struct FOptionSettings
    {
        ESimulationOption Option;
        TMap<FString, FString> Settings;

        explicit FOptionSettings(ESimulationOption InOption)
            : Option(InOption)
        {
        }

        FOptionSettings() : Option(ESimulationOption::Reconnection) {}

        void UpdateSetting(const FString& Key, const FString& Value)
        {
            Settings.Add(Key, Value);
            UE_LOG(LogTemp, Log, TEXT("Option '%s' updated setting '%s' to '%s'."), *OptionToString(Option), *Key, *Value);
        }

        void DisplaySettings() const
        {
            UE_LOG(LogTemp, Log, TEXT("Settings for Option: %s"), *OptionToString(Option));
            for (const TPair<FString, FString>& Pair : Settings)
            {
                UE_LOG(LogTemp, Log, TEXT("  %s: %s"), *Pair.Key, *Pair.Value);
            }
        }
    };

    static FString OptionToString(ESimulationOption Option)
    {
        switch (Option)
        {
        case ESimulationOption::Reconnection:         return TEXT("Reconnection");
        case ESimulationOption::CreateSensors:        return TEXT("CreateSensors");
        case ESimulationOption::EmotionalEditor:      return TEXT("EmotionalEditor");
        case ESimulationOption::SimulationCloning:    return TEXT("SimulationCloning");
        case ESimulationOption::FrequencyControl:     return TEXT("FrequencyControl");
        case ESimulationOption::DestructionModifier:  return TEXT("DestructionModifier");
        case ESimulationOption::CreationModifier:     return TEXT("CreationModifier");
        case ESimulationOption::CreationSystem:       return TEXT("CreationSystem");
        case ESimulationOption::DestructionSystem:    return TEXT("DestructionSystem");
        case ESimulationOption::EditingManipulator:   return TEXT("EditingManipulator");
        case ESimulationOption::NetworkConnector:     return TEXT("NetworkConnector");
        case ESimulationOption::ServerAdjustment:     return TEXT("ServerAdjustment");
        case ESimulationOption::DomainModifying:      return TEXT("DomainModifying");
        default:                                      return TEXT("Unknown");
        }
    }

    void InitializeOptions();
    void UpdateOptionSetting(ESimulationOption Option, const FString& Key, const FString& Value);
    void AutomateOptionUpdates();

    // Data: Option -> Settings
    TMap<ESimulationOption, FOptionSettings> SimulationOptions;

    // Timer
    float SettingsUpdateTimer = 0.f;
};

