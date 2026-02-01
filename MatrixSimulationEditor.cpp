#include "MatrixSimulationEditor.h"

#include "Misc/Guid.h"

AMatrixSimulationEditor::AMatrixSimulationEditor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationEditor::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Automated Matrix Simulation Editor Initialized."));

    // Initialize default settings
    AddSetting(TEXT("Sensitivity"), 50.f);
}

void AMatrixSimulationEditor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment the task timer
    TaskTimer += DeltaSeconds;

    // Perform automated tasks at regular intervals
    if (TaskTimer >= TaskInterval)
    {
        PerformAutomatedTasks();
        TaskTimer = 0.f; // Reset the timer
    }
}

void AMatrixSimulationEditor::AddSetting(const FString& Name, float InitialValue)
{
    if (Settings.Contains(Name))
    {
        UE_LOG(LogTemp, Warning, TEXT("Setting '%s' already exists."), *Name);
        return;
    }

    Settings.Add(Name, FEditorSetting(Name, InitialValue));
    UE_LOG(LogTemp, Log, TEXT("Setting Added: %s = %.2f"), *Name, InitialValue);
}

void AMatrixSimulationEditor::UpdateSetting(const FString& Name, float NewValue)
{
    if (FEditorSetting* Found = Settings.Find(Name))
    {
        Found->UpdateValue(NewValue);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Setting '%s' not found."), *Name);
    }
}

void AMatrixSimulationEditor::ExecuteCommand(const FString& CommandText)
{
    FEditorCommand Command(CommandText);
    Commands.Add(Command);

    UE_LOG(LogTemp, Log, TEXT("Command Executed - ID: %s, Text: %s"), *Command.CommandID, *Command.CommandText);

    // Simulate transferring power from the Infinity Matrix
    TransferPowerToEditor(CommandText);
}

void AMatrixSimulationEditor::TransferPowerToEditor(const FString& CommandText) const
{
    const float PowerConsumption = CalculatePower(CommandText);
    UE_LOG(LogTemp, Log, TEXT("Power Transferred from Infinity Matrix: %.2f units for command '%s'"), PowerConsumption, *CommandText);
}

float AMatrixSimulationEditor::CalculatePower(const FString& CommandText) const
{
    const float BasePower = static_cast<float>(CommandText.Len()) * 2.f; // based on length
    const float Sensitivity = Settings.Contains(TEXT("Sensitivity")) ? Settings[TEXT("Sensitivity")].Value : 50.f;
    return BasePower * (Sensitivity / 100.f);
}

void AMatrixSimulationEditor::RevertCommand(const FString& CommandID)
{
    int32 IndexToRemove = INDEX_NONE;
    for (int32 i = 0; i < Commands.Num(); ++i)
    {
        if (Commands[i].CommandID == CommandID)
        {
            IndexToRemove = i;
            break;
        }
    }

    if (IndexToRemove != INDEX_NONE)
    {
        const FString Text = Commands[IndexToRemove].CommandText;
        Commands.RemoveAt(IndexToRemove);
        UE_LOG(LogTemp, Log, TEXT("Command Reverted - ID: %s, Text: %s"), *CommandID, *Text);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Command with ID '%s' not found."), *CommandID);
    }
}

void AMatrixSimulationEditor::DisplaySettings() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all editor settings..."));
    for (const TPair<FString, FEditorSetting>& Pair : Settings)
    {
        UE_LOG(LogTemp, Log, TEXT("Setting: %s = %.2f"), *Pair.Value.Name, Pair.Value.Value);
    }
}

void AMatrixSimulationEditor::DisplayCommands() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all executed commands..."));
    for (const FEditorCommand& Command : Commands)
    {
        UE_LOG(LogTemp, Log, TEXT("Command - ID: %s, Text: %s"), *Command.CommandID, *Command.CommandText);
    }
}

void AMatrixSimulationEditor::PerformAutomatedTasks()
{
    UE_LOG(LogTemp, Log, TEXT("Performing automated editor tasks..."));

    // Execute automated commands dynamically
    ExecuteCommand(FString::Printf(TEXT("AutoCommand_%d"), Commands.Num()));

    // Update sensitivity randomly
    if (FMath::FRand() > 0.5f)
    {
        UpdateSetting(TEXT("Sensitivity"), FMath::FRandRange(10.f, 90.f));
    }

    // Revert the oldest command if the list exceeds a certain size
    if (Commands.Num() > 10)
    {
        RevertCommand(Commands[0].CommandID);
    }

    // Display the current state
    DisplaySettings();
    DisplayCommands();
}

