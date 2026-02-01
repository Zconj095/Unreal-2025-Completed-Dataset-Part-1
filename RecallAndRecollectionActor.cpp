#include "RecallAndRecollectionActor.h"

ARecallAndRecollectionActor::ARecallAndRecollectionActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARecallAndRecollectionActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<URecallAndRecollectionManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Recall Manager
    Manager->InitializeNetwork(/*inputSize*/4, /*hiddenNeurons*/10, /*outputSize*/2);

    // Simulate Recall Data
    Manager->AddRecallData(100, 0.05, 10, 0.8);  // M = 100, Beta = 0.05, t = 10, C = 0.8
    Manager->AddRecallData(90, 0.07, 15, 0.7);
    Manager->AddRecallData(110, 0.04, 8, 0.9);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Recall and Recollection for New Data
    double PredRecall = 0.0, PredRecollection = 0.0;
    Manager->PredictRecallAndRecollection(95, 0.06, 12, 0.85, PredRecall, PredRecollection);
    UE_LOG(LogTemp, Log, TEXT("Predicted Recall: %f"), PredRecall);
    UE_LOG(LogTemp, Log, TEXT("Predicted Recollection: %f"), PredRecollection);

    // Test Formula Calculation
    const double CalcRecall = Manager->CalculateRecall(95, 0.06, 12);
    const double CalcRecollection = Manager->CalculateRecollection(CalcRecall, 0.85);
    UE_LOG(LogTemp, Log, TEXT("Calculated Recall (Formula): %f"), CalcRecall);
    UE_LOG(LogTemp, Log, TEXT("Calculated Recollection (Formula): %f"), CalcRecollection);
}

