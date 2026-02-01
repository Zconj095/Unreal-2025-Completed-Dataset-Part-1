#include "AstronomicalMemoryEncodingComponent.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAstronomicalMemoryEncodingComponent::UAstronomicalMemoryEncodingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAstronomicalMemoryEncodingComponent::BeginPlay()
{
	Super::BeginPlay();

	const float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	PreviousTime = CurrentTime;
	PreviousComplexity = CalculateAstronomicalComplexity(PreviousTime);
	MemoryCapacity = 0.0f;
}

void UAstronomicalMemoryEncodingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetWorld() || DeltaTime <= 0.0f)
	{
		return;
	}

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float CurrentComplexity = CalculateAstronomicalComplexity(CurrentTime);

	const float AverageComplexity = (CurrentComplexity + PreviousComplexity) * 0.5f;
	const float IntegrationStep = Alpha * AverageComplexity * (CurrentTime - PreviousTime);

	MemoryCapacity += IntegrationStep;

	PreviousTime = CurrentTime;
	PreviousComplexity = CurrentComplexity;

	UE_LOG(LogTemp, Log, TEXT("Memory Capacity (M_a): %0.4f"), MemoryCapacity);
}

float UAstronomicalMemoryEncodingComponent::CalculateAstronomicalComplexity(float TimeSeconds) const
{
	return InitialComplexity * FMath::Exp(GrowthRate * TimeSeconds);
}

void UAstronomicalMemoryEncodingComponent::ResetMemory()
{
	MemoryCapacity = 0.0f;
	const float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
	PreviousTime = CurrentTime;
	PreviousComplexity = CalculateAstronomicalComplexity(CurrentTime);
}
