#include "MatrixSimulationAnalyzer.h"
#include "Engine/World.h"

#include "Misc/Guid.h"

AMatrixSimulationAnalyzer::AMatrixSimulationAnalyzer()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationAnalyzer::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Simulation Analyzer Initialized."));
}

void AMatrixSimulationAnalyzer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timer
    DataCollectionTimer += DeltaSeconds;

    // Automate data collection
    if (DataCollectionTimer >= DataCollectionInterval)
    {
        const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
        CollectSimulationData(FString::Printf(TEXT("Simulation Data Input at %.2fs."), TimeSeconds));
        DataCollectionTimer = 0.f; // Reset timer
    }
}

void AMatrixSimulationAnalyzer::CollectSimulationData(const FString& Content)
{
    FSimulationData Data(Content);
    CollectedData.Add(Data);
    UE_LOG(LogTemp, Log, TEXT("Simulation Data Collected - ID: %s, Content: %s"), *Data.DataID, *Content);
    ProcessData(Data);
}

void AMatrixSimulationAnalyzer::ProcessData(const FSimulationData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("Processing Data - ID: %s, Content: %s"), *Data.DataID, *Data.Content);
    SendToMainframe(Data);
}

void AMatrixSimulationAnalyzer::SendToMainframe(const FSimulationData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("Sending Data to Matrix Cortex Mainframe - ID: %s, Content: %s"), *Data.DataID, *Data.Content);
    StoreData(Data);
}

void AMatrixSimulationAnalyzer::StoreData(const FSimulationData& Data)
{
    UE_LOG(LogTemp, Log, TEXT("Data Stored in Mainframe - ID: %s, Content: %s"), *Data.DataID, *Data.Content);
}

void AMatrixSimulationAnalyzer::RetrieveCollectedData() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving all collected simulation data..."));
    for (const FSimulationData& Data : CollectedData)
    {
        UE_LOG(LogTemp, Log, TEXT("Data - ID: %s, Content: %s"), *Data.DataID, *Data.Content);
    }

    if (CollectedData.Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("No simulation data collected."));
    }
}

