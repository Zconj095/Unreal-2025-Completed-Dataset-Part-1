#include "BiochemicalOscillationPotentialComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalOscillationPotentialComponent::UBiochemicalOscillationPotentialComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBiochemicalOscillationPotentialComponent::BeginPlay()
{
	Super::BeginPlay();
	OscillationPotential = CalculateBOP(InitialFlux, DampingCoefficient, Frequency, 0.0f);
}

void UBiochemicalOscillationPotentialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	OscillationPotential = CalculateBOP(InitialFlux, DampingCoefficient, Frequency, TimeSeconds);

	if (bLogPotential)
	{
		UE_LOG(LogTemp, Log, TEXT("Time: %0.2f s, Biochemical Oscillation Potential (Φb): %0.2f"), TimeSeconds, OscillationPotential);
	}
}

float UBiochemicalOscillationPotentialComponent::CalculateBOP(float Flux, float Damping, float W, float TimeSeconds) const
{
	return Flux * FMath::Exp(-Damping * TimeSeconds) * FMath::Cos(W * TimeSeconds);
}
