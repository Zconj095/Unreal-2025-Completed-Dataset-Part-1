// Converted from Unity C# to Unreal C++
#include "SystemAdministrationInterface.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationInterface::ASystemAdministrationInterface()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationInterface::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("Automated System Administration Interface Initialized."));

    // Initial setup
    CreateVirtualConnection(TEXT("Axis-A"), TEXT("Axis-B"), 27.5f);
    CreateVirtualConnection(TEXT("Axis-C"), TEXT("Axis-D"), 42.8f);

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Add a new connection every 10 seconds (delay 2s)
        TM.SetTimer(
            TimerHandle_AutoAdd,
            this,
            &ASystemAdministrationInterface::AutoAddConnection,
            10.0f,
            true,
            2.0f);

        // Analyze connections every 15 seconds (delay 5s)
        TM.SetTimer(
            TimerHandle_AutoAnalyze,
            this,
            &ASystemAdministrationInterface::AutoAnalyzeConnections,
            15.0f,
            true,
            5.0f);

        // Execute bounce-back every 20 seconds (delay 8s)
        TM.SetTimer(
            TimerHandle_AutoBounce,
            this,
            &ASystemAdministrationInterface::AutoBounceBack,
            20.0f,
            true,
            8.0f);
    }
}

void ASystemAdministrationInterface::CreateVirtualConnection(const FString& InputAxis, const FString& OutputAxis, float Frequency)
{
    FVirtualConnection Conn(InputAxis, OutputAxis, Frequency);
    VirtualConnections.Add(Conn);
    UE_LOG(LogTemp, Log, TEXT("New Virtual Connection Created - ID: %s, Input: %s, Output: %s, Frequency: %.2f Hz"), *Conn.ConnectionID, *InputAxis, *OutputAxis, Frequency);
}

void ASystemAdministrationInterface::AnalyzeAllConnections() const
{
    UE_LOG(LogTemp, Log, TEXT("Analyzing all virtual connections..."));
    for (const FVirtualConnection& Conn : VirtualConnections)
    {
        Conn.AnalyzeConnection();
    }
}

void ASystemAdministrationInterface::ExecuteBounceBack() const
{
    UE_LOG(LogTemp, Log, TEXT("Executing bounce-back on all virtual connections..."));
    for (const FVirtualConnection& Conn : VirtualConnections)
    {
        Conn.BounceBack();
    }
}

void ASystemAdministrationInterface::AutoAddConnection()
{
    const FString InputAxis = FString::Printf(TEXT("Axis-%d"), FMath::RandRange(1, 9));
    const FString OutputAxis = FString::Printf(TEXT("Axis-%d"), FMath::RandRange(11, 19));
    const float Frequency = FMath::FRandRange(20.f, 100.f);
    CreateVirtualConnection(InputAxis, OutputAxis, Frequency);
}

void ASystemAdministrationInterface::AutoAnalyzeConnections()
{
    AnalyzeAllConnections();
}

void ASystemAdministrationInterface::AutoBounceBack()
{
    ExecuteBounceBack();
}

