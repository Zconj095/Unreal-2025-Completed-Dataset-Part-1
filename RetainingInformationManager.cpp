#include "RetainingInformationManager.h"
#include "Math/UnrealMathUtility.h"

double URetainingInformationManager::CalculateRetentionRate(double InitialRetention, double Alpha, double Time) const
{
    return InitialRetention * FMath::Exp(-Alpha * Time);
}

double URetainingInformationManager::CalculateLearningRate(double KnowledgeGained, double TimeElapsed) const
{
    if (TimeElapsed == 0.0)
    {
        UE_LOG(LogTemp, Error, TEXT("Time elapsed cannot be zero. Returning 0 for learning rate."));
        return 0.0;
    }
    return KnowledgeGained / TimeElapsed;
}

double URetainingInformationManager::CalculateRetentionInfluencedLearningRate(double RetentionRate, double LearningRate) const
{
    return RetentionRate * LearningRate;
}

