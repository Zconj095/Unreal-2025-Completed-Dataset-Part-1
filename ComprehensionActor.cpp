#include "ComprehensionActor.h"

AComprehensionActor::AComprehensionActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AComprehensionActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UComprehensionManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Comprehension Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Comprehension Data
    Manager->AddComprehensionData(50.0, 100.0, 0.8); // Ip, Ic, Focus
    Manager->AddComprehensionData(70.0, 120.0, 0.9);
    Manager->AddComprehensionData(60.0, 110.0, 0.85);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Comprehension for New Data
    const double Predicted = Manager->PredictComprehension(55.0, 115.0, 0.88);
    UE_LOG(LogTemp, Log, TEXT("Predicted Comprehension: %f"), Predicted);

    // Test Formula Calculation
    const double Calculated = Manager->CalculateComprehension(55.0, 115.0, 0.88);
    UE_LOG(LogTemp, Log, TEXT("Calculated Comprehension (Formula): %f"), Calculated);
}

