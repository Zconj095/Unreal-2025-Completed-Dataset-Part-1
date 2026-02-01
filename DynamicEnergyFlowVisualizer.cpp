#include "DynamicEnergyFlowVisualizer.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

ADynamicEnergyFlowVisualizer::ADynamicEnergyFlowVisualizer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADynamicEnergyFlowVisualizer::BeginPlay()
{
	Super::BeginPlay();

	if (DeltaTime <= 0.0f || Steps < 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicEnergyFlowVisualizer requires positive DeltaTime and Steps."));
		return;
	}

	const FVector Origin = GetActorLocation();

	for (int32 Index = 0; Index <= Steps; ++Index)
	{
		const float Time = Index * DeltaTime;
		const float Energy = CalculateEnergyFlow(Time);
		const FVector PointLocation = Origin + FVector(Time, Energy, 0.0f);

		if (PointActorClass && GetWorld())
		{
			// Spawn a representation actor at the sampled position.
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			GetWorld()->SpawnActor<AActor>(PointActorClass, PointLocation, FRotator::ZeroRotator, SpawnParams);
		}

		UE_LOG(LogTemp, Log, TEXT("Time: %.2f hours, Energy: %.4f"), Time, Energy);
	}
}

float ADynamicEnergyFlowVisualizer::CalculateEnergyFlow(float TimeSeconds) const
{
	const float Damped = FMath::Exp(-DampingCoefficient * TimeSeconds);
	return InitialAmplitude * Damped * FMath::Cos(AngularFrequency * TimeSeconds);
}
