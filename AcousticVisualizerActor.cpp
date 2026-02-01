#include "AcousticVisualizerActor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"

AAcousticVisualizerActor::AAcousticVisualizerActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAcousticVisualizerActor::BeginPlay()
{
	Super::BeginPlay();

	if (!IntensityPointClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AcousticVisualizerActor: IntensityPointClass is not set."));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (float Distance = 0.0f; Distance <= MaxDistance; Distance += Step)
	{
		const float Intensity = UAcousticSignal::CalculateIntensity(InitialIntensity, AttenuationCoefficient, Distance);

		// In Unreal, Z is "up", so use Intensity as height on Z.
		const FVector Location(Distance, 0.0f, Intensity);

		AActor* Spawned = World->SpawnActor<AActor>(IntensityPointClass, Location, FRotator::ZeroRotator);
		if (Spawned)
		{
			UE_LOG(LogTemp, Log, TEXT("Distance: %0.2f m, Intensity: %0.4f"), Distance, Intensity);
		}
	}
}

