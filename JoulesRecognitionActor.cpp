#include "JoulesRecognitionActor.h"

AJoulesRecognitionActor::AJoulesRecognitionActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AJoulesRecognitionActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UJoulesRecognitionManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Joules Recognition Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Memory Operations
    Manager->AddMemoryOperation(TArray<double>{1.0, 2.0, 3.0}, 0.05);
    Manager->AddMemoryOperation(TArray<double>{2.0, 3.0, 4.0}, 0.07);
    Manager->AddMemoryOperation(TArray<double>{3.0, 4.0, 5.0}, 0.09);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Calculate Average Joules
    const double AverageJoules = Manager->CalculateAverageJoules();
    UE_LOG(LogTemp, Log, TEXT("Average Joules Consumption: %f Joules"), AverageJoules);

    // Predict Joules Consumption
    const TArray<double> TestFeatures { 4.0, 5.0, 6.0 };
    const double Predicted = Manager->PredictJoules(TestFeatures);
    UE_LOG(LogTemp, Log, TEXT("Predicted Joules for Input [4,5,6]: %f Joules"), Predicted);
}

