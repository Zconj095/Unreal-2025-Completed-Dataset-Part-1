#include "MatrixSimulationCustomInterface.h"

AMatrixSimulationCustomInterface::AMatrixSimulationCustomInterface()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationCustomInterface::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Simulation Custom Interface Initialized."));
    InitializeOptions();
}

void AMatrixSimulationCustomInterface::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timer
    SettingsUpdateTimer += DeltaSeconds;

    // Automate settings updates every interval
    if (SettingsUpdateTimer >= SettingsUpdateInterval)
    {
        AutomateOptionUpdates();
        SettingsUpdateTimer = 0.f; // Reset timer
    }
}

void AMatrixSimulationCustomInterface::InitializeOptions()
{
    const int32 NumOptions = static_cast<int32>(ESimulationOption::Count);
    for (int32 i = 0; i < NumOptions; ++i)
    {
        ESimulationOption Option = static_cast<ESimulationOption>(i);
        SimulationOptions.Add(Option, FOptionSettings(Option));
        UE_LOG(LogTemp, Log, TEXT("Initialized Option: %s"), *OptionToString(Option));
    }
}

void AMatrixSimulationCustomInterface::UpdateOptionSetting(ESimulationOption Option, const FString& Key, const FString& Value)
{
    if (FOptionSettings* Found = SimulationOptions.Find(Option))
    {
        Found->UpdateSetting(Key, Value);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Option '%s' not found."), *OptionToString(Option));
    }
}

void AMatrixSimulationCustomInterface::DisplayAllOptions() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all simulation options and their settings..."));
    for (const TPair<ESimulationOption, FOptionSettings>& Pair : SimulationOptions)
    {
        Pair.Value.DisplaySettings();
    }
}

void AMatrixSimulationCustomInterface::AutomateOptionUpdates()
{
    UE_LOG(LogTemp, Log, TEXT("Automating simulation option updates..."));

    // Example automated updates
    UpdateOptionSetting(ESimulationOption::FrequencyControl, TEXT("Max Frequency"), FString::Printf(TEXT("%d Hz"), FMath::RandRange(50, 200)));
    UpdateOptionSetting(ESimulationOption::CreationModifier, TEXT("Creation Rate"), FString::Printf(TEXT("%d units/s"), FMath::RandRange(1, 100)));
    UpdateOptionSetting(ESimulationOption::DestructionSystem, TEXT("Destruction Threshold"), FString::FromInt(FMath::RandRange(0, 500)));

    // Display updated settings
    DisplayAllOptions();
}

