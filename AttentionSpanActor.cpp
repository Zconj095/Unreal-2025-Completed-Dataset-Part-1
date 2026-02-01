#include "AttentionSpanActor.h"

AAttentionSpanActor::AAttentionSpanActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAttentionSpanActor::BeginPlay()
{
    Super::BeginPlay();

    AttentionManager = NewObject<UAttentionSpanManager>(this);
    if (!ensure(AttentionManager)) { return; }

    AttentionManager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Attention Span Data
    AttentionManager->AddAttentionData(120.0, 2.0, 0.1);   // TFocus, D, Lambda
    AttentionManager->AddAttentionData(100.0, 3.0, 0.2);
    AttentionManager->AddAttentionData(150.0, 1.0, 0.05);

    // Train Neural Network
    const double FinalError = AttentionManager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Attention Span
    const double Predicted = AttentionManager->PredictAttentionSpan(140.0, 2.0, 0.15);
    UE_LOG(LogTemp, Log, TEXT("Predicted Attention Span: %f minutes"), Predicted);

    // Test Formula Calculation
    const double Calculated = AttentionManager->CalculateAttentionSpan(140.0, 2.0, 0.15);
    UE_LOG(LogTemp, Log, TEXT("Calculated Attention Span (Formula): %f minutes"), Calculated);
}

