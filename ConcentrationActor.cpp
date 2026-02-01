#include "ConcentrationActor.h"

AConcentrationActor::AConcentrationActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AConcentrationActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UConcentrationManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Concentration Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Concentration Data
    Manager->AddConcentrationData(80.0, 20.0, 0.1);  // F, D, sigma
    Manager->AddConcentrationData(90.0, 15.0, 0.08);
    Manager->AddConcentrationData(70.0, 25.0, 0.12);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Concentration for New Data
    const double Predicted = Manager->PredictConcentration(85.0, 18.0, 0.09);
    UE_LOG(LogTemp, Log, TEXT("Predicted Concentration: %f"), Predicted);

    // Test Formula Calculation
    const double Calculated = Manager->CalculateConcentration(85.0, 18.0, 0.09);
    UE_LOG(LogTemp, Log, TEXT("Calculated Concentration (Formula): %f"), Calculated);
}

