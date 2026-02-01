#include "BiochemicalMemoryEncodingComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalMemoryEncodingComponent::UBiochemicalMemoryEncodingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiochemicalMemoryEncodingComponent::BeginPlay()
{
	Super::BeginPlay();
	MemoryCapacity = CalculateBiochemicalMemory();
	UE_LOG(LogTemp, Log, TEXT("Biochemical Memory Encoding (M_b): %0.4f"), MemoryCapacity);
}

float UBiochemicalMemoryEncodingComponent::BiochemicalComplexity(float TimeSeconds) const
{
	return FMath::Sin(TimeSeconds) + 2.0f;
}

float UBiochemicalMemoryEncodingComponent::CalculateBiochemicalMemory()
{
	const float dt = (EndTime - StartTime) / FMath::Max(IntegrationSteps, 1);
	float Sum = 0.0f;

	for (int32 Step = 0; Step < IntegrationSteps; ++Step)
	{
		const float Time = StartTime + Step * dt;
		const float Complexity = BiochemicalComplexity(Time);
		Sum += EncodingEfficiency * Complexity * dt;
	}

	return Sum;
}
