#include "MemoryPreprocessingSpeedActor.h"
#include "HAL/PlatformTime.h"

AMemoryPreprocessingSpeedActor::AMemoryPreprocessingSpeedActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMemoryPreprocessingSpeedActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMemoryPreprocessingSpeedManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Preprocessing Speed Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Preprocessing Tasks and Measure Time
    AddPreprocessingTimer(TArray<double>{1.0, 2.0, 3.0});
    AddPreprocessingTimer(TArray<double>{2.0, 3.0, 4.0});
    AddPreprocessingTimer(TArray<double>{3.0, 4.0, 5.0});

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Calculate Average Preprocessing Time
    const double AvgUs = Manager->CalculateAveragePreprocessingTime();
    UE_LOG(LogTemp, Log, TEXT("Average Memory Preprocessing Time: %f us"), AvgUs);

    // Predict Preprocessing Time for New Features
    const TArray<double> TestFeatures { 4.0, 5.0, 6.0 };
    const double PredUs = Manager->PredictPreprocessingTime(TestFeatures);
    UE_LOG(LogTemp, Log, TEXT("Predicted Preprocessing Time for Features [4,5,6]: %f us"), PredUs);
}

void AMemoryPreprocessingSpeedActor::AddPreprocessingTimer(const TArray<double>& Features)
{
    const double StartSec = FPlatformTime::Seconds();

    // Simulate preprocessing task
    SimulatePreprocessing(Features);

    const double EndSec = FPlatformTime::Seconds();
    const double TimeUs = (EndSec - StartSec) * 1e6; // microseconds

    Manager->AddPreprocessingData(Features, TimeUs);
    UE_LOG(LogTemp, Log, TEXT("Measured Preprocessing Time: %f us for Features [%f, %f, %f]"),
        TimeUs,
        Features.IsValidIndex(0) ? Features[0] : 0.0,
        Features.IsValidIndex(1) ? Features[1] : 0.0,
        Features.IsValidIndex(2) ? Features[2] : 0.0);
}

void AMemoryPreprocessingSpeedActor::SimulatePreprocessing(const TArray<double>& Features)
{
    // Simulate a workload for preprocessing (e.g., data normalization, feature scaling)
    volatile double Result = 0.0; // volatile to avoid optimization
    for (double v : Features)
    {
        Result += FMath::Sqrt(v);
    }
    (void)Result; // silence unused warning
}

