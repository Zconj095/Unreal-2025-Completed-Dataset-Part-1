#include "SolarFeedbackLoopComponent.h"

#include "Math/UnrealMathUtility.h"

USolarFeedbackLoopComponent::USolarFeedbackLoopComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarFeedbackLoopComponent::BeginPlay()
{
    Super::BeginPlay();
    UpdatedFeedback = InitialFeedback;
}

void USolarFeedbackLoopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UpdatedFeedback = CalculateFeedback(UpdatedFeedback, ObservedSolarData, ExpectedSolarData, AdaptationRate);
    UE_LOG(LogTemp, Log, TEXT("Updated Feedback (Fn+1): %.2f"), UpdatedFeedback);
}

float USolarFeedbackLoopComponent::CalculateFeedback(float Feedback, float Observed, float Expected, float Beta) const
{
    return Feedback + Beta * (Observed - Expected);
}
