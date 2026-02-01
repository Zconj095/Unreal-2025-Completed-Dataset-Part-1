// Converted from Unity C# to Unreal C++
#include "SystemAdministrationDriverSystem.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationDriverSystem::ASystemAdministrationDriverSystem()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationDriverSystem::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("System Administration Driver System Initialized."));

    // Initial setup
    CreateDriver(TEXT("Core Driver"), 100.f);
    CreateDriver(TEXT("Secondary Driver"), 80.f);

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Create a new driver every 10 seconds (delay 2s)
        TM.SetTimer(
            TimerHandle_AutoCreate,
            this,
            &ASystemAdministrationDriverSystem::AutoCreateDriver,
            10.0f,
            true,
            2.0f);

        // Synchronize drivers every 15 seconds (delay 5s)
        TM.SetTimer(
            TimerHandle_AutoSync,
            this,
            &ASystemAdministrationDriverSystem::AutoSynchronizeDrivers,
            15.0f,
            true,
            5.0f);

        // Execute tasks every 20 seconds (delay 10s)
        TM.SetTimer(
            TimerHandle_AutoExecute,
            this,
            &ASystemAdministrationDriverSystem::AutoExecuteTasks,
            20.0f,
            true,
            10.0f);

        // Display drivers every 30 seconds (delay 12s)
        TM.SetTimer(
            TimerHandle_Display,
            this,
            &ASystemAdministrationDriverSystem::DisplayDrivers,
            30.0f,
            true,
            12.0f);
    }
}

void ASystemAdministrationDriverSystem::CreateDriver(const FString& Name, float BaseStrength)
{
    FDriver NewDriver(Name, BaseStrength);
    Drivers.Add(NewDriver);
    UE_LOG(LogTemp, Log, TEXT("Driver Created - ID: %s, Name: %s, Strength: %.2f"), *NewDriver.DriverID, *Name, NewDriver.CommandStrength);
}

void ASystemAdministrationDriverSystem::SynchronizeDrivers()
{
    UE_LOG(LogTemp, Log, TEXT("Synchronizing all drivers..."));
    for (FDriver& D : Drivers)
    {
        D.Synchronize();
    }
    UE_LOG(LogTemp, Log, TEXT("All drivers synchronized successfully."));
}

void ASystemAdministrationDriverSystem::ExecuteTaskAcrossDrivers(const FString& Task)
{
    UE_LOG(LogTemp, Log, TEXT("Executing task '%s' across all drivers..."), *Task);
    for (const FDriver& D : Drivers)
    {
        D.ExecuteTask(Task);
    }
}

void ASystemAdministrationDriverSystem::DisplayDrivers() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all drivers..."));
    for (const FDriver& D : Drivers)
    {
        D.Display();
    }
}

void ASystemAdministrationDriverSystem::AutoCreateDriver()
{
    static const TArray<FString> DriverNames = { TEXT("Auxiliary Driver"), TEXT("Tertiary Driver"), TEXT("Backup Driver"), TEXT("Quantum Driver") };
    const FString Name = DriverNames[FMath::RandRange(0, DriverNames.Num() - 1)];
    const float BaseStrength = FMath::FRandRange(50.f, 150.f);
    CreateDriver(Name, BaseStrength);
}

void ASystemAdministrationDriverSystem::AutoSynchronizeDrivers()
{
    SynchronizeDrivers();
}

void ASystemAdministrationDriverSystem::AutoExecuteTasks()
{
    static const TArray<FString> Tasks = { TEXT("Optimize Network Performance"), TEXT("Enhance Security Protocols"), TEXT("Load Balance System"), TEXT("Debug Matrix Errors") };
    const FString Task = Tasks[FMath::RandRange(0, Tasks.Num() - 1)];
    ExecuteTaskAcrossDrivers(Task);
}

