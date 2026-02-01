#include "RetainingInformationActor.h"

ARetainingInformationActor::ARetainingInformationActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ARetainingInformationActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<URetainingInformationManager>(this);
    if (!ensure(Manager)) { return; }

    // Example Initial Data
    const double InitialRetention = 100.0; // Ret0
    const double Alpha = 0.05;             // forgetting rate
    const double Time = 10.0;              // elapsed time

    // Calculate Retention Rate
    const double RetentionRate = Manager->CalculateRetentionRate(InitialRetention, Alpha, Time);
    UE_LOG(LogTemp, Log, TEXT("Retention Rate after %f units of time: %f"), Time, RetentionRate);

    // Example for Learning Rate
    const double KnowledgeGained = 50.0; // dK
    const double TimeElapsed = 5.0;      // dt
    const double LearningRate = Manager->CalculateLearningRate(KnowledgeGained, TimeElapsed);
    UE_LOG(LogTemp, Log, TEXT("Learning Rate: %f"), LearningRate);

    // Retention-Influenced Learning Rate
    const double RetentionInfluencedLearningRate = Manager->CalculateRetentionInfluencedLearningRate(RetentionRate, LearningRate);
    UE_LOG(LogTemp, Log, TEXT("Retention-Influenced Learning Rate: %f"), RetentionInfluencedLearningRate);
}

