#include "EcosystemVisualizer.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

AEcosystemVisualizer::AEcosystemVisualizer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEcosystemVisualizer::BeginPlay()
{
	Super::BeginPlay();

	const float Stability = CalculateStability();
	UE_LOG(LogTemp, Log, TEXT("Ecosystem Stability: %.4f"), Stability);

	if (!SpeciesClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpeciesClass is not assigned."));
		return;
	}

	const int32 SpawnCount = FMath::Max(1, FMath::RoundToInt(SpeciesRichness));
	for (int32 Index = 0; Index < SpawnCount; ++Index)
	{
		const int32 Column = Index % GridColumns;
		const int32 Row = Index / GridColumns;
		const FVector Offset(Column * GridSpacing, Row * GridSpacing, 0.0f);
		const FVector SpawnLocation = GetActorLocation() + Offset;
		const FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		GetWorld()->SpawnActor<AActor>(SpeciesClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

float AEcosystemVisualizer::CalculateStability() const
{
	const float Denominator = Alpha + Beta;
	if (Denominator <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	return (SpeciesRichness * InteractionStrength) / Denominator;
}
