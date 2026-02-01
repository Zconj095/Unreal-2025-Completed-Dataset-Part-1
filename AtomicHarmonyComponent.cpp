#include "AtomicHarmonyComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAtomicHarmonyComponent::UAtomicHarmonyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAtomicHarmonyComponent::BeginPlay()
{
	Super::BeginPlay();
	SimulationTime = 0.0f;
	AtomicHarmony = CalculateAtomicHarmony(SimulationTime);
}

void UAtomicHarmonyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SimulationTime += DeltaTime;
	AtomicHarmony = CalculateAtomicHarmony(SimulationTime);

	if (bLogHarmony)
	{
		UE_LOG(LogTemp, Log, TEXT("Atomic Harmony (Ha) at time %0.2f: %0.4f"), SimulationTime, AtomicHarmony);
	}
}

float UAtomicHarmonyComponent::CalculateAtomicHarmony(float TimeSeconds) const
{
	const float Angular = 2.0f * PI * InteractionFrequency * TimeSeconds;
	return BaselineHarmony * (1.0f + Sensitivity * FMath::Sin(Angular));
}

void UAtomicHarmonyComponent::ResetHarmonyTime()
{
	SimulationTime = 0.0f;
	AtomicHarmony = CalculateAtomicHarmony(SimulationTime);
}
