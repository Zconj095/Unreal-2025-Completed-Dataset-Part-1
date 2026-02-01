#include "AttentionListeningAndHearingActor.h"
#include "Engine/World.h"

AAttentionListeningAndHearingActor::AAttentionListeningAndHearingActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAttentionListeningAndHearingActor::BeginPlay()
{
    Super::BeginPlay();

    // Initialize Auditory Manager (UObject)
    AuditoryManager = NewObject<UAttentionListeningAndHearingManager>(this);
    if (!ensure(AuditoryManager)) { return; }

    AuditoryManager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/2);

    // Simulate Auditory Data
    AuditoryManager->AddAuditoryData(80.0, 20.0, 50.0);
    AuditoryManager->AddAuditoryData(70.0, 30.0, 60.0);
    AuditoryManager->AddAuditoryData(90.0, 10.0, 40.0);

    // Train Neural Network
    const double FinalError = AuditoryManager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Auditory Responses for New Data
    double PredAl = 0.0, PredH = 0.0;
    AuditoryManager->PredictAuditoryResponse(85.0, 25.0, 55.0, PredAl, PredH);
    UE_LOG(LogTemp, Log, TEXT("Predicted Auditory Attention: %f"), PredAl);
    UE_LOG(LogTemp, Log, TEXT("Predicted Hearing: %f"), PredH);

    // Test Formula Calculation
    const double Al = AuditoryManager->CalculateAuditoryAttention(85.0, 25.0);
    const double H  = AuditoryManager->CalculateHearing(85.0, 25.0, 55.0);
    UE_LOG(LogTemp, Log, TEXT("Calculated Auditory Attention (Formula): %f"), Al);
    UE_LOG(LogTemp, Log, TEXT("Calculated Hearing (Formula): %f"), H);
}

