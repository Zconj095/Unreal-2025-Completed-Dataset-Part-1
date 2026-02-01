#include "MemoryRetentionRateActor.h"

AMemoryRetentionRateActor::AMemoryRetentionRateActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMemoryRetentionRateActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMemoryRetentionRateManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Retention Rate Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Retention Data
    Manager->AddRetentionData(100, 0.05, 10);  // M0 = 100, Alpha = 0.05, t = 10
    Manager->AddRetentionData(90, 0.07, 15);
    Manager->AddRetentionData(110, 0.04, 8);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Retention Rate for New Data
    const double PredictedRetention = Manager->PredictMemoryRetentionRate(95, 0.06, 12);
    UE_LOG(LogTemp, Log, TEXT("Predicted Retention Rate: %f"), PredictedRetention);

    // Test Formula Calculation
    const double CalculatedRetention = Manager->CalculateMemoryRetentionRate(95, 0.06, 12);
    UE_LOG(LogTemp, Log, TEXT("Calculated Retention Rate (Formula): %f"), CalculatedRetention);
}

