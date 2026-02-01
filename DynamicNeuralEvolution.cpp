#include "DynamicNeuralEvolution.h"

ADynamicNeuralEvolution::ADynamicNeuralEvolution()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralEvolution::BeginPlay()
{
	Super::BeginPlay();

	CurrentNeuralSize = InitialNeuralSize;
	ElapsedTime = 0.0f;
	UE_LOG(LogTemp, Log, TEXT("Initial Neural Size (N0): %.2f"), CurrentNeuralSize);
}

void ADynamicNeuralEvolution::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ElapsedTime >= TotalTime)
	{
		return;
	}

	if (TimeStep <= 0.0f || CarryingCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralEvolution requires positive TimeStep and CarryingCapacity."));
		return;
	}

	CurrentNeuralSize = SimulateEvolution(CurrentNeuralSize, GrowthRate, CarryingCapacity, TimeStep);
	ElapsedTime += TimeStep;
	UE_LOG(LogTemp, Log, TEXT("Time: %.2fs, Neural Size (N): %.2f"), ElapsedTime, CurrentNeuralSize);
}

float ADynamicNeuralEvolution::SimulateEvolution(float CurrentSize, float Beta, float Capacity, float Delta) const
{
	const float dNdt = Beta * CurrentSize * (1.0f - CurrentSize / Capacity);
	return CurrentSize + dNdt * Delta;
}
