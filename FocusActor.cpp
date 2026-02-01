#include "FocusActor.h"

AFocusActor::AFocusActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AFocusActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UFocusManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Focus Manager
    Manager->InitializeNetwork(/*inputSize*/2, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Focus Data
    Manager->AddFocusData(30.0, 100.0); // Rc, Tc
    Manager->AddFocusData(50.0, 120.0);
    Manager->AddFocusData(45.0, 110.0);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Focus for New Data
    const double Predicted = Manager->PredictFocus(40.0, 105.0);
    UE_LOG(LogTemp, Log, TEXT("Predicted Focus: %f"), Predicted);

    // Test Formula Calculation
    const double Calculated = Manager->CalculateFocus(40.0, 105.0);
    UE_LOG(LogTemp, Log, TEXT("Calculated Focus (Formula): %f"), Calculated);
}

