#include "BiochemicalMemoryEncoding2Component.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalMemoryEncoding2Component::UBiochemicalMemoryEncoding2Component()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBiochemicalMemoryEncoding2Component::BeginPlay()
{
	Super::BeginPlay();
	MemoryCapacity = 0.0f;
}

float UBiochemicalMemoryEncoding2Component::CalculateBc(float TimeSeconds) const
{
	return FMath::Sin(TimeSeconds) + 1.0f;
}

float UBiochemicalMemoryEncoding2Component::UpdateMemoryCapacity(float CurrentBc)
{
	HistoricalBc.Add(CurrentBc);

	if (HistoricalBc.Num() < 2)
	{
		return 0.0f;
	}

	float Result = 0.0f;
	for (int32 Index = 1; Index < HistoricalBc.Num(); ++Index)
	{
		const float BcAverage = (HistoricalBc[Index - 1] + HistoricalBc[Index]) * 0.5f;
		Result += Alpha * BcAverage * IntegrationInterval;
	}

	MemoryCapacity = Result;
	return MemoryCapacity;
}
