#include "MemoryPreAllocationSpeedActor.h"
#include "HAL/PlatformTime.h"

AMemoryPreAllocationSpeedActor::AMemoryPreAllocationSpeedActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMemoryPreAllocationSpeedActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMemoryPreAllocationSpeedManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Pre-allocation Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Pre-allocation and Measure Time
    AddPreAllocationTimer(TArray<double>{1.0, 2.0, 3.0});
    AddPreAllocationTimer(TArray<double>{2.0, 3.0, 4.0});
    AddPreAllocationTimer(TArray<double>{3.0, 4.0, 5.0});

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Calculate Average Pre-allocation Time
    const double AvgUs = Manager->CalculateAveragePreAllocationTime();
    UE_LOG(LogTemp, Log, TEXT("Average Memory Pre-allocation Time: %f us"), AvgUs);

    // Predict Pre-allocation Time for New Features
    const TArray<double> TestFeatures { 4.0, 5.0, 6.0 };
    const double PredUs = Manager->PredictPreAllocationTime(TestFeatures);
    UE_LOG(LogTemp, Log, TEXT("Predicted Pre-allocation Time for Features [4,5,6]: %f us"), PredUs);
}

void AMemoryPreAllocationSpeedActor::AddPreAllocationTimer(const TArray<double>& Features)
{
    const double StartSec = FPlatformTime::Seconds();

    // Simulate memory pre-allocation
    SimulatePreAllocation(Features);

    const double EndSec = FPlatformTime::Seconds();
    const double TimeUs = (EndSec - StartSec) * 1e6; // microseconds

    Manager->AddPreAllocationData(Features, TimeUs);
    UE_LOG(LogTemp, Log, TEXT("Measured Pre-allocation Time: %f us for Features [%f, %f, %f]"),
        TimeUs,
        Features.IsValidIndex(0) ? Features[0] : 0.0,
        Features.IsValidIndex(1) ? Features[1] : 0.0,
        Features.IsValidIndex(2) ? Features[2] : 0.0);
}

void AMemoryPreAllocationSpeedActor::SimulatePreAllocation(const TArray<double>& Features)
{
    // Simulate pre-allocation workload (e.g., reserving memory blocks)
    int32 Size = 1;
    if (Features.Num() >= 3)
    {
        const double prod = Features[0] * Features[1] * Features[2];
        Size = FMath::Clamp(static_cast<int32>(prod), 1, 1000000); // clamp for safety
    }
    TArray<int32> PreAllocated;
    PreAllocated.SetNumUninitialized(Size);
}

