#include "MemoryAllocationSpeedActor.h"
#include "HAL/PlatformTime.h"

AMemoryAllocationSpeedActor::AMemoryAllocationSpeedActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMemoryAllocationSpeedActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMemoryAllocationSpeedManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Allocation Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Memory Allocation and Measure Time
    AddAllocationTimer(TArray<double>{1.0, 2.0, 3.0});
    AddAllocationTimer(TArray<double>{2.0, 3.0, 4.0});
    AddAllocationTimer(TArray<double>{3.0, 4.0, 5.0});

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Calculate Average Allocation Time
    const double AvgUs = Manager->CalculateAverageAllocationTime();
    UE_LOG(LogTemp, Log, TEXT("Average Memory Allocation Time: %f bcs"), AvgUs);

    // Predict Allocation Time for New Features
    const TArray<double> TestFeatures { 4.0, 5.0, 6.0 };
    const double PredUs = Manager->PredictAllocationTime(TestFeatures);
    UE_LOG(LogTemp, Log, TEXT("Predicted Allocation Time for Features [4,5,6]: %f bcs"), PredUs);
}

void AMemoryAllocationSpeedActor::AddAllocationTimer(const TArray<double>& Features)
{
    const double StartSec = FPlatformTime::Seconds();

    // Simulate memory allocation operation
    SimulateMemoryAllocation(Features);

    const double EndSec = FPlatformTime::Seconds();
    const double AllocationTimeUs = (EndSec - StartSec) * 1e6; // microseconds

    Manager->AddAllocationData(Features, AllocationTimeUs);
    UE_LOG(LogTemp, Log, TEXT("Measured Allocation Time: %f bcs for Features [%f, %f, %f]"),
        AllocationTimeUs,
        Features.IsValidIndex(0) ? Features[0] : 0.0,
        Features.IsValidIndex(1) ? Features[1] : 0.0,
        Features.IsValidIndex(2) ? Features[2] : 0.0);
}

void AMemoryAllocationSpeedActor::SimulateMemoryAllocation(const TArray<double>& Features)
{
    // Simulate memory allocation workload (e.g., array creation, object initialization)
    int32 Size = 1;
    if (Features.Num() >= 3)
    {
        const double prod = Features[0] * Features[1] * Features[2];
        Size = FMath::Clamp(static_cast<int32>(prod), 1, 1000000); // clamp to avoid runaway allocs
    }
    TArray<int32> SimulatedMemory;
    SimulatedMemory.SetNumUninitialized(Size);
    // Touch the memory to avoid optimization away
    for (int32 i = 0; i < Size; ++i) { SimulatedMemory[i] = i; }
}

