#include "CelestialResonanceComponent.h"
#include "Engine/World.h"

#include "GameFramework/Actor.h"

UCelestialResonanceComponent::UCelestialResonanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCelestialResonanceComponent::BeginPlay()
{
	Super::BeginPlay();
	ResonanceFactor = CalculateResonance(0.0f);
	UE_LOG(LogTemp, Log, TEXT("Celestial Resonance Factor (R_a): %.4f"), ResonanceFactor);
}

void UCelestialResonanceComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();
	ResonanceFactor = CalculateResonance(TimeSeconds);
	UE_LOG(LogTemp, Log, TEXT("Celestial Resonance Factor (R_a): %.4f"), ResonanceFactor);
}

float UCelestialResonanceComponent::CalculateResonance(float TimeSeconds) const
{
	const float SafePeriod = FMath::Max(Period, KINDA_SMALL_NUMBER);
	return Amplitude * FMath::Cos((2 * PI * TimeSeconds) / SafePeriod);
}
