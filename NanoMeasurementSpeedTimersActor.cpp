#include "NanoMeasurementSpeedTimersActor.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Math/UnrealMathUtility.h"

ANanoMeasurementSpeedTimersActor::ANanoMeasurementSpeedTimersActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANanoMeasurementSpeedTimersActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UNanoMeasurementSpeedTimersManager>(this);
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
    UE_LOG(LogTemp, Log, TEXT("Average Nano Measurement Time: %f ns"), AverageTime);

    // Predict NanoSeconds for New Features
    TArray<double> TestFeatures = { 4.0, 5.0, 6.0 };
    const double PredictedTime = Manager->PredictNanoSeconds(TestFeatures);

    FString FeaturesStr;
    for (int i = 0; i < TestFeatures.Num(); ++i)
    {
        FeaturesStr += FString::SanitizeFloat(TestFeatures[i]);
        if (i + 1 < TestFeatures.Num()) FeaturesStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Predicted Nano Measurement Time for Features %s: %f ns"), *FeaturesStr, PredictedTime);
}

void ANanoMeasurementSpeedTimersActor::AddOperationTimer(const TArray<double>& Features)
{
    const double StartSec = FPlatformTime::Seconds();

    // Simulate operation (replace with actual work)
    SimulateOperation(Features);

    const double EndSec = FPlatformTime::Seconds();
    const double NanoSeconds = (EndSec - StartSec) * 1e9;

    Manager->AddTimerData(Features, NanoSeconds);

    FString FeaturesStr;
    for (int i = 0; i < Features.Num(); ++i)
    {
        FeaturesStr += FString::SanitizeFloat(Features[i]);
        if (i + 1 < Features.Num()) FeaturesStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Measured Time: %f ns for Features %s"), NanoSeconds, *FeaturesStr);
}

void ANanoMeasurementSpeedTimersActor::SimulateOperation(const TArray<double>& /*Features*/)
{
    // Simulate 1-3 ms delay
    const float SleepSeconds = FMath::FRandRange(0.001f, 0.003f);
    FPlatformProcess::Sleep(SleepSeconds);
}

