// Converted from Unity C# to Unreal C++
#include "SystemAdministrationAccuracyNetwork.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationAccuracyNetwork::ASystemAdministrationAccuracyNetwork()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationAccuracyNetwork::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("System Administration Accuracy Network Initialized."));

    // Automate actions similar to Unity's InvokeRepeating
    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Generate packets every 10 seconds, initial delay 2s
        TM.SetTimer(
            TimerHandle_AutoGenerate,
            this,
            &ASystemAdministrationAccuracyNetwork::AutoGeneratePackets,
            10.0f,
            true,
            2.0f);

        // Process packets every 8 seconds, initial delay 5s
        TM.SetTimer(
            TimerHandle_ProcessNext,
            this,
            &ASystemAdministrationAccuracyNetwork::ProcessNextPacket,
            8.0f,
            true,
            5.0f);

        // Display output every 20 seconds, initial delay 15s
        TM.SetTimer(
            TimerHandle_DisplayOutput,
            this,
            &ASystemAdministrationAccuracyNetwork::DisplayOutputChannel,
            20.0f,
            true,
            15.0f);
    }
}

void ASystemAdministrationAccuracyNetwork::AddDataPacket(const FString& Content, const FString& Source, const FString& Destination, bool bIsAuthorized)
{
    FSystemAdminDataPacket Packet(Content, Source, Destination, bIsAuthorized);
    InputChannel.Enqueue(Packet);
    UE_LOG(LogTemp, Log, TEXT("Data Packet Added - ID: %s, Content: %s, Source: %s, Destination: %s, Authorized: %s"),
        *Packet.PacketID, *Content, *Source, *Destination, bIsAuthorized ? TEXT("true") : TEXT("false"));
}

void ASystemAdministrationAccuracyNetwork::ProcessNextPacket()
{
    if (InputChannel.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No data packets to process in the input channel."));
        return;
    }

    FSystemAdminDataPacket Packet;
    const bool bDequeued = InputChannel.Dequeue(Packet);
    if (bDequeued)
    {
        ProcessDataPacket(Packet);
    }
}

void ASystemAdministrationAccuracyNetwork::ProcessDataPacket(FSystemAdminDataPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Processing Data Packet - ID: %s, Source: %s, Destination: %s"), *Packet.PacketID, *Packet.Source, *Packet.Destination);

    if (Packet.bIsAuthorized)
    {
        const FString SafeRoute = CalculateSafeRoute(Packet.Source, Packet.Destination);
        UE_LOG(LogTemp, Log, TEXT("Data Packet routed safely to: %s"), *SafeRoute);
        TransferToHeadAdmin(Packet);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unauthorized Data Packet detected. Packet ID: %s has been blocked."), *Packet.PacketID);
    }
}

FString ASystemAdministrationAccuracyNetwork::CalculateSafeRoute(const FString& Source, const FString& Destination) const
{
    // Simplified logic for determining a safer route
    return FString::Printf(TEXT("%s -> IntermediateNode -> %s"), *Source, *Destination);
}

void ASystemAdministrationAccuracyNetwork::TransferToHeadAdmin(FSystemAdminDataPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Transferring Data Packet to HeadAdmin - ID: %s"), *Packet.PacketID);
    CatalogData(Packet);
}

void ASystemAdministrationAccuracyNetwork::CatalogData(FSystemAdminDataPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Cataloging Data Packet into Master Matrix Code Database - Content: %s"), *Packet.Content);
    EncodeData(Packet);
}

void ASystemAdministrationAccuracyNetwork::EncodeData(const FSystemAdminDataPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Encoding Data Packet for Network Systems - Packet ID: %s"), *Packet.PacketID);
    OutputChannel.Add(Packet);
}

void ASystemAdministrationAccuracyNetwork::DisplayOutputChannel()
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all packets in the output channel..."));
    for (const FSystemAdminDataPacket& Packet : OutputChannel)
    {
        UE_LOG(LogTemp, Log, TEXT("Packet ID: %s, Content: %s, Destination: %s"), *Packet.PacketID, *Packet.Content, *Packet.Destination);
    }
}

void ASystemAdministrationAccuracyNetwork::AutoGeneratePackets()
{
    static const TArray<FString> Sources = { TEXT("NodeA"), TEXT("NodeB"), TEXT("NodeC") };
    static const TArray<FString> Destinations = { TEXT("NodeD"), TEXT("NodeE"), TEXT("NodeF") };

    const FString Content = TEXT("Automated Data Content");
    const int32 SourceIdx = FMath::RandRange(0, Sources.Num() - 1);
    const int32 DestIdx = FMath::RandRange(0, Destinations.Num() - 1);
    const FString& Source = Sources[SourceIdx];
    const FString& Destination = Destinations[DestIdx];
    const bool bAuthorized = (FMath::RandRange(0, 1) == 1);

    AddDataPacket(Content, Source, Destination, bAuthorized);
}

