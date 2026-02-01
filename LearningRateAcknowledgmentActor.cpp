#include "LearningRateAcknowledgmentActor.h"

ALearningRateAcknowledgmentActor::ALearningRateAcknowledgmentActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALearningRateAcknowledgmentActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<ULearningRateAcknowledgmentManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Learning Rate Manager
    Manager->InitializeNetwork(/*inputSize*/2, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Learning Data
    Manager->AddLearningData(50.0, 10.0);
    Manager->AddLearningData(40.0, 8.0);
    Manager->AddLearningData(60.0, 12.0);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Learning Rate for New Data
    const double Predicted = Manager->PredictLearningRate(45.0, 9.0);
    UE_LOG(LogTemp, Log, TEXT("Predicted Learning Rate: %f"), Predicted);

    // Test Formula Calculation
    const double Calculated = Manager->CalculateLearningRate(45.0, 9.0);
    UE_LOG(LogTemp, Log, TEXT("Calculated Learning Rate (Formula): %f"), Calculated);
}

