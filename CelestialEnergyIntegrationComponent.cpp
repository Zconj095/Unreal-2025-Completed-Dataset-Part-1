#include "CelestialEnergyIntegrationComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"

UCelestialEnergyIntegrationComponent::UCelestialEnergyIntegrationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCelestialEnergyIntegrationComponent::BeginPlay()
{
	Super::BeginPlay();
	PreviousTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

void UCelestialEnergyIntegrationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetWorld())
	{
		return;
	}

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float DeltaT = CurrentTime - PreviousTime;

	const float Value = EnergyDistribution.Eval(CurrentTime, 0.0f);
	IntegratedEnergy += EnergyFlux * Value * DeltaT;

	PreviousTime = CurrentTime;

	UE_LOG(LogTemp, Log, TEXT("Integrated Energy (E_a): %0.4f"), IntegratedEnergy);
}
