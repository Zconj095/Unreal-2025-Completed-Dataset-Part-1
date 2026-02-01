#include "BrainwaveLunarResonanceComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBrainwaveLunarResonanceComponent::UBrainwaveLunarResonanceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBrainwaveLunarResonanceComponent::BeginPlay()
{
	Super::BeginPlay();
	ResonanceFactor = CalculateBLR(Amplitude, LunarPhasePeriod, 0.0f);
}

void UBrainwaveLunarResonanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	ResonanceFactor = CalculateBLR(Amplitude, LunarPhasePeriod, TimeSeconds);
	UE_LOG(LogTemp, Log, TEXT("Time: %0.2f s, Resonance Factor (R_l): %0.4f"), TimeSeconds, ResonanceFactor);
}

float UBrainwaveLunarResonanceComponent::CalculateBLR(float AmplitudeValue, float PhasePeriod, float TimeSeconds) const
{
	if (PhasePeriod <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lunar phase period must be greater than zero."));
		return 0.0f;
	}

	return AmplitudeValue * FMath::Sin((2.0f * PI * TimeSeconds) / PhasePeriod);
}
