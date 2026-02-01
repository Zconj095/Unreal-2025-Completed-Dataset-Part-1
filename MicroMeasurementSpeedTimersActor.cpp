#include "MicroMeasurementSpeedTimersActor.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Math/UnrealMathUtility.h"

AMicroMeasurementSpeedTimersActor::AMicroMeasurementSpeedTimersActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMicroMeasurementSpeedTimersActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMicroMeasurementSpeedTimersManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Timer Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Operations and Measure Time
    AddOperationTimer({ 1.0, 2.0, 3.0 });
    AddOperationTimer({ 2.0, 3.0, 4.0 });
    AddOperationTimer({ 3.0, 4.0, 5.0 });

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Calculate Average Time
    const double AverageTime = Manager->CalculateAverageTime();
    UE_LOG(LogTemp, Log, TEXT("Average Micro Measurement Time: %f us"), AverageTime);

    // Predict MicroSeconds for New Features
    TArray<double> TestFeatures = { 4.0, 5.0, 6.0 };
    const double PredictedTime = Manager->PredictMicroSeconds(TestFeatures);

    FString FeaturesStr;
    for (int i = 0; i < TestFeatures.Num(); ++i)
    {
        FeaturesStr += FString::SanitizeFloat(TestFeatures[i]);
        if (i + 1 < TestFeatures.Num()) FeaturesStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Predicted Micro Measurement Time for Features %s: %f us"), *FeaturesStr, PredictedTime);
}

void AMicroMeasurementSpeedTimersActor::AddOperationTimer(const TArray<double>& Features)
{
    const double StartSec = FPlatformTime::Seconds();

    // Simulate operation (replace with actual work)
    SimulateOperation(Features);

    const double EndSec = FPlatformTime::Seconds();
    const double MicroSeconds = (EndSec - StartSec) * 1e6;

    Manager->AddTimerData(Features, MicroSeconds);

    FString FeaturesStr;
    for (int i = 0; i < Features.Num(); ++i)
    {
        FeaturesStr += FString::SanitizeFloat(Features[i]);
        if (i + 1 < Features.Num()) FeaturesStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Measured Time: %f us for Features %s"), MicroSeconds, *FeaturesStr);
}

void AMicroMeasurementSpeedTimersActor::SimulateOperation(const TArray<double>& /*Features*/)
{
    // Simulate 1-3 ms delay
    const float SleepSeconds = FMath::FRandRange(0.001f, 0.003f);
    FPlatformProcess::Sleep(SleepSeconds);
}

