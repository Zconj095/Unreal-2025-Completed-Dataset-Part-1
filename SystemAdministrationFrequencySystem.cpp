// Converted from Unity C# to Unreal C++
#include "SystemAdministrationFrequencySystem.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationFrequencySystem::ASystemAdministrationFrequencySystem()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationFrequencySystem::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("System Administration Frequency System Initialized."));

    // Initial setup
    AddFrequencyChannel(TEXT("Channel Alpha"), 27.f, TEXT("Matrix Cortex Operations"));
    AddFrequencyChannel(TEXT("Channel Beta"), 42.f, TEXT("Infinity Matrix Synchronization"));

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Add a new channel every 10 seconds (delay 2s)
        TM.SetTimer(
            TimerHandle_AutoAdd,
            this,
            &ASystemAdministrationFrequencySystem::AutoAddFrequencyChannel,
            10.0f,
            true,
            2.0f);

        // Edit a random channel every 15 seconds (delay 5s)
        TM.SetTimer(
            TimerHandle_AutoEdit,
            this,
            &ASystemAdministrationFrequencySystem::AutoEditFrequencyChannel,
            15.0f,
            true,
            5.0f);

        // Display channels every 20 seconds (delay 10s)
        TM.SetTimer(
            TimerHandle_AutoDisplay,
            this,
            &ASystemAdministrationFrequencySystem::AutoDisplayFrequencyChannels,
            20.0f,
            true,
            10.0f);
    }
}

void ASystemAdministrationFrequencySystem::AddFrequencyChannel(const FString& Name, float Frequency, const FString& Purpose)
{
    FFrequencyChannel NewChannel(Name, Frequency, Purpose);
    FrequencyChannels.Add(NewChannel);
    UE_LOG(LogTemp, Log, TEXT("Frequency Channel Added - ID: %s, Name: %s, Frequency: %.2f Hz, Purpose: %s"), *NewChannel.ChannelID, *Name, Frequency, *Purpose);
}

void ASystemAdministrationFrequencySystem::EditFrequencyChannel(const FString& ChannelID, float NewFrequency)
{
    const int32 Index = FrequencyChannels.IndexOfByPredicate([&](const FFrequencyChannel& C){ return C.ChannelID == ChannelID; });
    if (Index != INDEX_NONE)
    {
        FrequencyChannels[Index].UpdateFrequency(NewFrequency);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Frequency Channel with ID '%s' not found."), *ChannelID);
    }
}

void ASystemAdministrationFrequencySystem::DisplayFrequencyChannels() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all frequency channels..."));
    for (const FFrequencyChannel& C : FrequencyChannels)
    {
        C.Display();
    }
}

void ASystemAdministrationFrequencySystem::AutoAddFrequencyChannel()
{
    static const TArray<FString> Purposes = { TEXT("Matrix Operations"), TEXT("System Synchronization"), TEXT("Signal Management"), TEXT("Data Transmission") };
    const int32 PurposeIdx = FMath::RandRange(0, Purposes.Num() - 1);
    const int32 ChannelNum = FMath::RandRange(100, 999);
    const FString Name = FString::Printf(TEXT("Channel %d"), ChannelNum);
    const float Freq = FMath::FRandRange(20.f, 100.f);
    AddFrequencyChannel(Name, Freq, Purposes[PurposeIdx]);
}

void ASystemAdministrationFrequencySystem::AutoEditFrequencyChannel()
{
    if (FrequencyChannels.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, FrequencyChannels.Num() - 1);
        const float NewFreq = FMath::FRandRange(20.f, 100.f);
        EditFrequencyChannel(FrequencyChannels[Index].ChannelID, NewFreq);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No frequency channels available to edit."));
    }
}

void ASystemAdministrationFrequencySystem::AutoDisplayFrequencyChannels()
{
    DisplayFrequencyChannels();
}

