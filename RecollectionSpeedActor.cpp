#include "RecollectionSpeedActor.h"

ARecollectionSpeedActor::ARecollectionSpeedActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARecollectionSpeedActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<URecollectionSpeedManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize
    Manager->InitializeNeuralNetwork(/*inputSize*/3, /*hiddenNeurons*/5, /*outputSize*/1);

    // Simulate Adding Recollection Data
    AddRecollectionEntryWithTiming({ 1.0, 2.0, 3.0 }, 1.5f, 3.0f);
    AddRecollectionEntryWithTiming({ 2.0, 3.0, 4.0 }, 2.0f, 4.0f);
    AddRecollectionEntryWithTiming({ 4.0, 5.0, 6.0 }, 1.0f, 2.5f);

    // Calculate Metrics
    const double Avg = Manager->CalculateAverageRecollectionSpeed();
    UE_LOG(LogTemp, Log, TEXT("Average Recollection Speed: %f seconds"), Avg);

    // Train
    Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);

    // Predict
    const TArray<double> TestFeatures = { 2.0, 3.0, 4.0 };
    const float Pred = Manager->PredictRecollectionSpeed(TestFeatures);
    UE_LOG(LogTemp, Log, TEXT("Predicted Recollection Speed for Features 2,3,4: %f seconds"), Pred);
}

void ARecollectionSpeedActor::AddRecollectionEntryWithTiming(const TArray<double>& Features, float RecallTime, float RetentionTime)
{
    Manager->AddRecollectionEntry(Features, RecallTime, RetentionTime);
}

