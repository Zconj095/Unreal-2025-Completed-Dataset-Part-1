#include "CircadianRhythmComponent.h"

UCircadianRhythmComponent::UCircadianRhythmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCircadianRhythmComponent::BeginPlay()
{
	Super::BeginPlay();
	RhythmState = CalculateRhythm(AccumulatedTime);
}

void UCircadianRhythmComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AccumulatedTime += DeltaTime;
	RhythmState = CalculateRhythm(AccumulatedTime);
	UE_LOG(LogTemp, Log, TEXT("Circadian Rhythm state at t=%.2f: %.4f"), AccumulatedTime, RhythmState);
}

float UCircadianRhythmComponent::CalculateRhythm(float TimeSeconds) const
{
	return Amplitude * FMath::Cos(Frequency * TimeSeconds + Phase);
}
