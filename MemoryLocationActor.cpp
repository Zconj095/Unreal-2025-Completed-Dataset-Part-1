#include "MemoryLocationActor.h"

AMemoryLocationActor::AMemoryLocationActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMemoryLocationActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMemoryLocationManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Memory Location Manager
    Manager->InitializeNeuralNetwork(/*inputSize*/3, /*hiddenNeurons*/5, /*outputSize*/2);

    // Simulate Memory Locations
    Manager->AddMemoryLocation(TEXT("Entry1"), FVector2D(2.0, 3.0), TArray<double>{1.0, 2.0, 3.0}, true);
    Manager->AddMemoryLocation(TEXT("Entry2"), FVector2D(4.0, 5.0), TArray<double>{2.0, 3.0, 4.0}, false);
    Manager->AddMemoryLocation(TEXT("Entry3"), FVector2D(6.0, 7.0), TArray<double>{4.0, 5.0, 6.0}, true);

    // Calculate Metrics
    const double AccessRate = Manager->CalculateAccessRate();
    UE_LOG(LogTemp, Log, TEXT("Access Rate: %f%%"), AccessRate * 100.0);

    const FVector2D AvgLoc = Manager->CalculateAverageLocation();
    UE_LOG(LogTemp, Log, TEXT("Average Memory Location: (%f, %f)"), AvgLoc.X, AvgLoc.Y);

    // Train Neural Network
    Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);

    // Predict Optimal Memory Location
    const FVector2D Pred = Manager->PredictOptimalLocation(TArray<double>{3.0, 4.0, 5.0});
    UE_LOG(LogTemp, Log, TEXT("Predicted Optimal Memory Location for Features [3,4,5]: (%f, %f)"), Pred.X, Pred.Y);
}

