#include "ChronoMagicalEnergyComponent.h"
#include "Engine/World.h"

#include "GameFramework/Actor.h"

UChronoMagicalEnergyComponent::UChronoMagicalEnergyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UChronoMagicalEnergyComponent::BeginPlay()
{
	Super::BeginPlay();
	EnergyFlow = CalculateEnergyFlow(0.0f);
}

void UChronoMagicalEnergyComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float TimeSeconds = GetWorld()->GetTimeSeconds();
	EnergyFlow = CalculateEnergyFlow(TimeSeconds);
	UE_LOG(LogTemp, Log, TEXT("Chrono Magical Energy at t=%.2f: %.4f"), TimeSeconds, EnergyFlow);
}

float UChronoMagicalEnergyComponent::CalculateEnergyFlow(float TimeSeconds) const
{
	const float Damped = FMath::Exp(-DampingCoefficient * TimeSeconds);
	return InitialAmplitude * Damped * FMath::Cos(AngularFrequency * TimeSeconds);
}
