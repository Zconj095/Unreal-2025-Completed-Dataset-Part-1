#include "DynamicGeologicalAdaptation.h"

ADynamicGeologicalAdaptation::ADynamicGeologicalAdaptation()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicGeologicalAdaptation::BeginPlay()
{
	Super::BeginPlay();

	CurrentNetworkSize = InitialNetworkSize;
}

void ADynamicGeologicalAdaptation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimeStep <= 0.0f || MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicGeologicalAdaptation requires positive TimeStep and MaxCapacity."));
		return;
	}

	CurrentNetworkSize = UpdateNeuralNetworkSize(CurrentNetworkSize, GrowthRate, MaxCapacity, TimeStep);
	UE_LOG(LogTemp, Log, TEXT("Current Network Size (N): %.2f"), CurrentNetworkSize);
}

float ADynamicGeologicalAdaptation::UpdateNeuralNetworkSize(float CurrentSize, float Beta, float Capacity, float Delta) const
{
	const float Growth = Beta * CurrentSize * (1.0f - CurrentSize / Capacity);
	return CurrentSize + Growth * Delta;
}
