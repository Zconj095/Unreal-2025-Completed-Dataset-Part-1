#include "ElementalFluxVisualizer.h"
#include "GameFramework/Actor.h"
#include "ElementalFluxVisualizer.h"
#include "ElementalCycleRestoration.h"
#include "Engine/World.h"

AElementalFluxVisualizer::AElementalFluxVisualizer()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AElementalFluxVisualizer::BeginPlay()
{
	Super::BeginPlay();

	if (!FluxPointClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("FluxPointClass is not assigned."));
		return;
	}

	UElementalCycleRestoration* Restoration = NewObject<UElementalCycleRestoration>();
	Restoration->DivergenceScale = DivergenceScale;
	Restoration->MagicDecay = MagicDecay;

	TArray<FVector> Points;
	Points.Add(FVector(1.0f, 2.0f, 3.0f));
	Points.Add(FVector(4.0f, 5.0f, 6.0f));
	Points.Add(FVector(7.0f, 8.0f, 9.0f));

	const double Flux = Restoration->ComputeFlux(Points);
	UE_LOG(LogTemp, Log, TEXT("Elemental Flux: %.2f"), Flux);

	for (int32 Index = 0; Index < Points.Num(); ++Index)
	{
		const FVector PointOffset = FVector(Points[Index].X * GridSpacing, Points[Index].Y * GridSpacing, Points[Index].Z * GridSpacing);
		const FVector PointLocation = GetActorLocation() + PointOffset;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		GetWorld()->SpawnActor<AActor>(FluxPointClass, PointLocation, FRotator::ZeroRotator, SpawnParams);
	}
}
