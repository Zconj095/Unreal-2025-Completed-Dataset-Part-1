// Converted from Unity C# to Unreal C++
#include "SystemAdministrationController.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationController::ASystemAdministrationController()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("System Administration Controller Initialized."));

    // Initial setup
    AddTask(TEXT("Initialize System Diagnostics"));
    AddOption(TEXT("Activate Debug Mode"), TEXT("+10% Performance Analysis"));

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Add a new task every 5 seconds (delay 2s)
        TM.SetTimer(
            TimerHandle_AutoAddTask,
            this,
            &ASystemAdministrationController::AutoAddTask,
            5.0f,
            true,
            2.0f);

        // Complete a task every 7 seconds (delay 3s)
        TM.SetTimer(
            TimerHandle_AutoCompleteTask,
            this,
            &ASystemAdministrationController::AutoCompleteTask,
            7.0f,
            true,
            3.0f);

        // Add a new option every 6 seconds (delay 4s)
        TM.SetTimer(
            TimerHandle_AutoAddOption,
            this,
            &ASystemAdministrationController::AutoAddOption,
            6.0f,
            true,
            4.0f);

        // Apply an option every 8 seconds (delay 5s)
        TM.SetTimer(
            TimerHandle_AutoApplyOption,
            this,
            &ASystemAdministrationController::AutoApplyOption,
            8.0f,
            true,
            5.0f);

        // Display tasks every 10 seconds (delay 10s)
        TM.SetTimer(
            TimerHandle_DisplayTasks,
            this,
            &ASystemAdministrationController::DisplayTasks,
            10.0f,
            true,
            10.0f);

        // Display options every 10 seconds (delay 12s)
        TM.SetTimer(
            TimerHandle_DisplayOptions,
            this,
            &ASystemAdministrationController::DisplayOptions,
            10.0f,
            true,
            12.0f);
    }
}

void ASystemAdministrationController::AddTask(const FString& Description)
{
    FAdminTask Task(Description);
    Tasks.Add(Task);
    UE_LOG(LogTemp, Log, TEXT("New Admin Task Added - ID: %s, Description: %s"), *Task.TaskID, *Description);
}

void ASystemAdministrationController::CompleteTask(const FString& TaskID)
{
    const int32 Index = Tasks.IndexOfByPredicate([&](const FAdminTask& T){ return T.TaskID == TaskID; });
    if (Index != INDEX_NONE)
    {
        Tasks[Index].bIsCompleted = true;
        UE_LOG(LogTemp, Log, TEXT("Task '%s' completed: %s"), *Tasks[Index].TaskID, *Tasks[Index].Description);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Task with ID '%s' not found."), *TaskID);
    }
}

void ASystemAdministrationController::AddOption(const FString& Name, const FString& Modifier)
{
    FAdminOption Option(Name, Modifier);
    Options.Add(Option);
    UE_LOG(LogTemp, Log, TEXT("New Admin Option Added - ID: %s, Name: %s, Modifier: %s"), *Option.OptionID, *Name, *Modifier);
}

void ASystemAdministrationController::ApplyOption(const FString& OptionID)
{
    const int32 Index = Options.IndexOfByPredicate([&](const FAdminOption& O){ return O.OptionID == OptionID; });
    if (Index != INDEX_NONE)
    {
        UE_LOG(LogTemp, Log, TEXT("Option '%s' applied with modifier: %s"), *Options[Index].Name, *Options[Index].Modifier);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Option with ID '%s' not found."), *OptionID);
    }
}

void ASystemAdministrationController::DisplayTasks() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all administrative tasks..."));
    for (const FAdminTask& T : Tasks)
    {
        UE_LOG(LogTemp, Log, TEXT("Task - ID: %s, Description: %s, Completed: %s"), *T.TaskID, *T.Description, T.bIsCompleted ? TEXT("true") : TEXT("false"));
    }
}

void ASystemAdministrationController::DisplayOptions() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all administrative options..."));
    for (const FAdminOption& O : Options)
    {
        UE_LOG(LogTemp, Log, TEXT("Option - ID: %s, Name: %s, Modifier: %s"), *O.OptionID, *O.Name, *O.Modifier);
    }
}

void ASystemAdministrationController::AutoAddTask()
{
    static const TArray<FString> TaskDescriptions = {
        TEXT("Reboot System Core"),
        TEXT("Optimize Network Speed"),
        TEXT("Check System Logs"),
        TEXT("Update Security Protocols")
    };
    const int32 Idx = FMath::RandRange(0, TaskDescriptions.Num() - 1);
    AddTask(TaskDescriptions[Idx]);
}

void ASystemAdministrationController::AutoCompleteTask()
{
    if (Tasks.Num() > 0)
    {
        const FString TaskID = Tasks[0].TaskID;
        CompleteTask(TaskID);
        Tasks.RemoveAt(0);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No tasks available to complete."));
    }
}

void ASystemAdministrationController::AutoAddOption()
{
    static const TArray<FString> OptionNames = { TEXT("Enable Encryption"), TEXT("Activate Firewall"), TEXT("Boost Performance"), TEXT("Load Balancer Adjustment") };
    static const TArray<FString> Modifiers   = { TEXT("+20% Security"),     TEXT("+15% Stability"),     TEXT("+10% Speed"),        TEXT("+25% Efficiency") };
    const int32 Idx = FMath::RandRange(0, OptionNames.Num() - 1);
    AddOption(OptionNames[Idx], Modifiers[Idx]);
}

void ASystemAdministrationController::AutoApplyOption()
{
    if (Options.Num() > 0)
    {
        const FString OptionID = Options[0].OptionID;
        ApplyOption(OptionID);
        Options.RemoveAt(0);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No options available to apply."));
    }
}

