#include "MatrixSimulationDataSystem.h"
#include "Engine/World.h"

#include "Misc/Guid.h"

AMatrixSimulationDataSystem::AMatrixSimulationDataSystem()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationDataSystem::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Automated Matrix Simulation Data System Initialized."));
}

void AMatrixSimulationDataSystem::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment the timer
    OperationTimer += DeltaSeconds;

    // Perform automated operations at regular intervals
    if (OperationTimer >= OperationInterval)
    {
        PerformAutomatedOperations();
        OperationTimer = 0.f; // Reset timer
    }
}

void AMatrixSimulationDataSystem::TransferData(const FString& Source, const FString& Destination, const FString& Content)
{
    FDataPacket Packet(Source, Destination, Content);
    UE_LOG(LogTemp, Log, TEXT("Data Packet Created - ID: %s, Source: %s, Destination: %s, Content: %s"), *Packet.PacketID, *Source, *Destination, *Content);

    // Send data to the analysis chamber
    SendToAnalysisChamber(Packet);
}

void AMatrixSimulationDataSystem::SendToAnalysisChamber(const FDataPacket& Packet)
{
    UE_LOG(LogTemp, Log, TEXT("Sending Data Packet to Analysis Chamber - ID: %s"), *Packet.PacketID);
    DataChamber.StoreData(Packet);
}

void AMatrixSimulationDataSystem::RetrieveRandomPacket()
{
    const int32 Count = DataChamber.GetCount();
    if (Count > 0)
    {
        const int32 RandomIndex = FMath::RandRange(0, Count - 1);
        FString PacketID;
        if (DataChamber.GetPacketIDAtIndex(RandomIndex, PacketID))
        {
            DataChamber.RetrieveDataByID(PacketID);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No data packets available for retrieval."));
    }
}

void AMatrixSimulationDataSystem::DisplayReservoirData() const
{
    DataChamber.DisplayAllData();
}

void AMatrixSimulationDataSystem::ClearReservoir()
{
    DataChamber.ClearReservoir();
}

void AMatrixSimulationDataSystem::PerformAutomatedOperations()
{
    UE_LOG(LogTemp, Log, TEXT("Performing automated data system operations..."));

    // Example operations
    const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
    TransferData(TEXT("SystemA"), TEXT("SystemB"), FString::Printf(TEXT("Automated data content at %.2f"), TimeSeconds));

    if (DataChamber.GetCount() > 0)
    {
        RetrieveRandomPacket();
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No data available to retrieve, skipping retrieval step."));
    }

    // Display the reservoir data for monitoring
    DisplayReservoirData();
}

