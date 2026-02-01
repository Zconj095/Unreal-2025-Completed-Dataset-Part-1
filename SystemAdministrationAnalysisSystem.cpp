// Converted from Unity C# to Unreal C++
#include "SystemAdministrationAnalysisSystem.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationAnalysisSystem::ASystemAdministrationAnalysisSystem()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationAnalysisSystem::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("System Administration Analysis System Initialized."));

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Auto-generate input every 5s, delay 2s
        TM.SetTimer(
            TimerHandle_AutoInput,
            this,
            &ASystemAdministrationAnalysisSystem::AutoGenerateInputPacket,
            5.0f,
            true,
            2.0f);

        // Auto-generate output every 7s, delay 3s
        TM.SetTimer(
            TimerHandle_AutoOutput,
            this,
            &ASystemAdministrationAnalysisSystem::AutoGenerateOutputPacket,
            7.0f,
            true,
            3.0f);

        // Process input every 6s, delay 4s
        TM.SetTimer(
            TimerHandle_ProcessNext,
            this,
            &ASystemAdministrationAnalysisSystem::ProcessNextPacket,
            6.0f,
            true,
            4.0f);

        // Display records every 15s, delay 10s
        TM.SetTimer(
            TimerHandle_DisplayRecords,
            this,
            &ASystemAdministrationAnalysisSystem::DisplayAdaptabilityRecords,
            15.0f,
            true,
            10.0f);
    }
}

void ASystemAdministrationAnalysisSystem::AddDataPacket(const FString& Content, const FString& Direction)
{
    FSystemAdminAnalysisPacket Packet(Content, Direction);
    if (Direction.Equals(TEXT("Input"), ESearchCase::IgnoreCase))
    {
        InputChannel.Enqueue(Packet);
    }
    else if (Direction.Equals(TEXT("Output"), ESearchCase::IgnoreCase))
    {
        // Store output packets in output channel (array for easy viewing)
        OutputChannel.Add(Packet);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid packet direction specified."));
    }

    UE_LOG(LogTemp, Log, TEXT("Data Packet Added - ID: %s, Content: %s, Direction: %s"), *Packet.PacketID, *Content, *Direction);
}

void ASystemAdministrationAnalysisSystem::AnalyzeDataPacket(FSystemAdminAnalysisPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Analyzing Packet - ID: %s, Direction: %s"), *Packet.PacketID, *Packet.Direction);
    Packet.MarkAnalyzed();

    // Simulate checking for adjustments
    if (Packet.Content.Contains(TEXT("Error")) || Packet.Content.Contains(TEXT("Patch")))
    {
        CreateAdaptabilityRecord(Packet.Content, TEXT("Error detected; patch required."));
    }

    // Catalog the data
    CatalogData(Packet);
}

void ASystemAdministrationAnalysisSystem::CreateAdaptabilityRecord(const FString& Content, const FString& AdjustmentDetails)
{
    FAdaptabilityRecord Record(Content, AdjustmentDetails);
    AdaptabilityRecords.Add(Record);
    UE_LOG(LogTemp, Log, TEXT("Adaptability Record Created - ID: %s, Content: %s, Adjustment: %s"), *Record.RecordID, *Content, *AdjustmentDetails);
}

void ASystemAdministrationAnalysisSystem::CatalogData(const FSystemAdminAnalysisPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Cataloging Packet into Master Database - ID: %s, Content: %s"), *Packet.PacketID, *Packet.Content);
    // Simulate moving analyzed packets to the output channel
    OutputChannel.Add(Packet);
}

void ASystemAdministrationAnalysisSystem::ProcessNextPacket()
{
    if (InputChannel.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No data packets to process in the input channel."));
        return;
    }

    FSystemAdminAnalysisPacket Packet;
    if (InputChannel.Dequeue(Packet))
    {
        AnalyzeDataPacket(Packet);
    }
}

void ASystemAdministrationAnalysisSystem::DisplayAdaptabilityRecords()
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all adaptability records..."));
    for (const FAdaptabilityRecord& Record : AdaptabilityRecords)
    {
        UE_LOG(LogTemp, Log, TEXT("Record ID: %s, Content: %s, Adjustment: %s"), *Record.RecordID, *Record.Content, *Record.AdjustmentDetails);
    }
}

void ASystemAdministrationAnalysisSystem::AutoGenerateInputPacket()
{
    AddDataPacket(TEXT("Routine Input Data"), TEXT("Input"));
}

void ASystemAdministrationAnalysisSystem::AutoGenerateOutputPacket()
{
    AddDataPacket(TEXT("Routine Output Data"), TEXT("Output"));
}

