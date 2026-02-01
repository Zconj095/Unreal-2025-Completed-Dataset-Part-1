#include "RetrievalRateActor.h"

ARetrievalRateActor::ARetrievalRateActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARetrievalRateActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<URetrievalRateManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Retrieval Rate Manager
    Manager->InitializeNeuralNetwork(/*inputSize*/3, /*hiddenNeurons*/5, /*outputSize*/1);

    // Simulate Retrieval Data
    AddRetrievalEntryWithTiming({ 1.0, 2.0, 3.0 }, true, 0.5f);
    AddRetrievalEntryWithTiming({ 2.0, 3.0, 4.0 }, false, 1.0f);
    AddRetrievalEntryWithTiming({ 4.0, 5.0, 6.0 }, true, 0.7f);

    // Calculate Metrics
    const double RetrievalRate = Manager->CalculateRetrievalRate();
    UE_LOG(LogTemp, Log, TEXT("Retrieval Rate: %f%%"), RetrievalRate * 100.0);

    const double AvgTime = Manager->CalculateAverageRetrievalTime();
    UE_LOG(LogTemp, Log, TEXT("Average Retrieval Time: %f seconds"), AvgTime);

    // Train Neural Network
    Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);

    // Test Retrieval Prediction
    const TArray<double> TestFeatures = { 2.0, 3.0, 4.0 };
    const float Predicted = Manager->PredictRetrievalLikelihood(TestFeatures);
    UE_LOG(LogTemp, Log, TEXT("Predicted Retrieval Likelihood for Features 2,3,4: %f%%"), Predicted * 100.0f);
}

void ARetrievalRateActor::AddRetrievalEntryWithTiming(const TArray<double>& Features, bool bIsRetrieved, float RetrievalTime)
{
    Manager->AddRetrievalEntry(Features, bIsRetrieved, RetrievalTime);
}

