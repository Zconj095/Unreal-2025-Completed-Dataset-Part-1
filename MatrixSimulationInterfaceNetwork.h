#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationInterfaceNetwork.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationInterfaceNetwork : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationInterfaceNetwork();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Network")
    void AddGrid();

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Network")
    void AddNodeToGrid(int32 GridIndex, const FVector& Position);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Network")
    void SynchronizeAllGrids();

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Network")
    void AdjustTiming(float NewTimingMs);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Network")
    void DisplayAllGrids() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float TaskInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Network")
    float TimingSynchronizationMs = 50.f; // Default timing in milliseconds

private:
    struct FGridNode
    {
        FVector Position = FVector::ZeroVector;
        FString NodeID;

        explicit FGridNode(const FVector& InPos)
            : Position(InPos)
            , NodeID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
        {
        }

        FGridNode() = default;
    };

    struct FNetworkGrid
    {
        FString GridID;
        TArray<FGridNode> Nodes;

        FNetworkGrid()
            : GridID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
        {
        }

        void AddNode(const FVector& Position)
        {
            FGridNode Node(Position);
            Nodes.Add(MoveTemp(Node));
            UE_LOG(LogTemp, Log, TEXT("Node Added - GridID: %s, NodeID: %s, Position: %s"), *GridID, *Nodes.Last().NodeID, *Nodes.Last().Position.ToString());
        }

        void SynchronizeNodes(float TimingMs) const
        {
            UE_LOG(LogTemp, Log, TEXT("Synchronizing Nodes in Grid '%s' with timing: %.2fms"), *GridID, TimingMs);
            for (const FGridNode& Node : Nodes)
            {
                UE_LOG(LogTemp, Log, TEXT("Node '%s' synchronized at position %s"), *Node.NodeID, *Node.Position.ToString());
            }
        }
    };

    void PerformAutomatedTasks();

    // Data
    TArray<FNetworkGrid> NetworkGrids;

    // Timer
    float TaskTimer = 0.f;
};

