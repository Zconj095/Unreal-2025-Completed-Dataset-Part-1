#include "MatrixSimulationInterfaceNetwork.h"

#include "Misc/Guid.h"

AMatrixSimulationInterfaceNetwork::AMatrixSimulationInterfaceNetwork()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationInterfaceNetwork::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Automated Matrix Simulation Interface Network Initialized."));
}

void AMatrixSimulationInterfaceNetwork::Tick(float DeltaSeconds)
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

void AMatrixSimulationInterfaceNetwork::AddGrid()
{
    FNetworkGrid Grid;
    UE_LOG(LogTemp, Log, TEXT("Grid Added - GridID: %s"), *Grid.GridID);
    NetworkGrids.Add(MoveTemp(Grid));
}

void AMatrixSimulationInterfaceNetwork::AddNodeToGrid(int32 GridIndex, const FVector& Position)
{
    if (NetworkGrids.IsValidIndex(GridIndex))
    {
        NetworkGrids[GridIndex].AddNode(Position);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Grid index '%d' is out of range."), GridIndex);
    }
}

void AMatrixSimulationInterfaceNetwork::SynchronizeAllGrids()
{
    UE_LOG(LogTemp, Log, TEXT("Synchronizing all grids with timing: %.2fms"), TimingSynchronizationMs);
    for (const FNetworkGrid& Grid : NetworkGrids)
    {
        Grid.SynchronizeNodes(TimingSynchronizationMs);
    }
}

void AMatrixSimulationInterfaceNetwork::AdjustTiming(float NewTimingMs)
{
    TimingSynchronizationMs = FMath::Clamp(NewTimingMs, 10.f, 500.f);
    UE_LOG(LogTemp, Log, TEXT("Timing Synchronization adjusted to: %.2fms"), TimingSynchronizationMs);
}

void AMatrixSimulationInterfaceNetwork::DisplayAllGrids() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all grids and their nodes..."));
    for (int32 i = 0; i < NetworkGrids.Num(); ++i)
    {
        const FNetworkGrid& Grid = NetworkGrids[i];
        UE_LOG(LogTemp, Log, TEXT("Grid %d - ID: %s, Nodes Count: %d"), i + 1, *Grid.GridID, Grid.Nodes.Num());
        for (const FGridNode& Node : Grid.Nodes)
        {
            UE_LOG(LogTemp, Log, TEXT("  Node - ID: %s, Position: %s"), *Node.NodeID, *Node.Position.ToString());
        }
    }
}

void AMatrixSimulationInterfaceNetwork::PerformAutomatedTasks()
{
    UE_LOG(LogTemp, Log, TEXT("Performing automated network tasks..."));

    // Automatically add a grid if there are no grids
    if (NetworkGrids.Num() == 0)
    {
        AddGrid();
    }

    // Automatically add a node to the last grid
    const int32 LastIndex = NetworkGrids.Num() - 1;
    const int32 RX = FMath::RandRange(-10, 9); // Unity int Range(-10,10) -> -10..9
    const int32 RZ = FMath::RandRange(-10, 9);
    AddNodeToGrid(LastIndex, FVector(static_cast<float>(RX), 0.f, static_cast<float>(RZ)));

    // Randomly adjust timing synchronization
    AdjustTiming(FMath::FRandRange(10.f, 500.f));

    // Synchronize all grids
    SynchronizeAllGrids();

    // Display the state of all grids
    DisplayAllGrids();
}

