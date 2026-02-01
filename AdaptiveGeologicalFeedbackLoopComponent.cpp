#include "AdaptiveGeologicalFeedbackLoopComponent.h"
#include "Logging/LogMacros.h"

UAdaptiveGeologicalFeedbackLoopComponent::UAdaptiveGeologicalFeedbackLoopComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAdaptiveGeologicalFeedbackLoopComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdatedFeedback = CurrentFeedback;
}

void UAdaptiveGeologicalFeedbackLoopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdatedFeedback = CalculateAGFL(CurrentFeedback, ObservedPhenomena, ExpectedOutcome, AdaptationRate);
	CurrentFeedback = UpdatedFeedback;

	UE_LOG(LogTemp, Verbose, TEXT("Geological Feedback Fn:%0.2f -> Fn+1:%0.2f (Og:%0.2f, Eg:%0.2f, α:%0.2f)"),
		CurrentFeedback, UpdatedFeedback, ObservedPhenomena, ExpectedOutcome, AdaptationRate);
}

float UAdaptiveGeologicalFeedbackLoopComponent::CalculateAGFL(float Fn, float Og, float Eg, float Alpha) const
{
	return Fn + Alpha * (Og - Eg);
}
