#include "CelestialPatternFeedbackComponent.h"

UCelestialPatternFeedbackComponent::UCelestialPatternFeedbackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCelestialPatternFeedbackComponent::BeginPlay()
{
	Super::BeginPlay();
	LogFeedback();
}

void UCelestialPatternFeedbackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FeedbackState += Beta * (ObservedPatterns - ExpectedPatterns);
	LogFeedback();
}

void UCelestialPatternFeedbackComponent::LogFeedback() const
{
	UE_LOG(LogTemp, Log, TEXT("Feedback State (F_n+1): %.4f"), FeedbackState);
}
