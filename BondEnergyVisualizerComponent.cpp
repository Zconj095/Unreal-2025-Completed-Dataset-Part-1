#include "BondEnergyVisualizerComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

static constexpr double PlancksConstant = 6.626e-34;
static constexpr double SpeedOfLight = 3.0e8;

UBondEnergyVisualizerComponent::UBondEnergyVisualizerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBondEnergyVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
	VisualizeBondEnergies();
}

void UBondEnergyVisualizerComponent::VisualizeBondEnergies()
{
	if (Wavelengths.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No wavelengths configured for visualization."));
		return;
	}

	const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
	for (int32 Index = 0; Index < Wavelengths.Num(); ++Index)
	{
		const float Wavelength = Wavelengths[Index];
		const float BondEnergy = CalculateBondEnergy(Wavelength);
		const float Height = BondEnergy * ScaleFactor;
		UE_LOG(LogTemp, Log, TEXT("Wavelength: %0.4e m, Bond Energy: %0.4e J"), Wavelength, BondEnergy);

		if (bDrawDebugBars && GetWorld())
		{
			const FVector Location = Origin + FVector(Index * BarSpacing, 0.0f, Height * 0.5f);
			const FVector Extents = FVector(BarSpacing * 0.25f, BarSpacing * 0.25f, Height * 0.5f);
			DrawDebugBox(GetWorld(), Location, Extents, FColor::Yellow, false, DebugDuration, 0, 2.0f);
		}
	}
}

float UBondEnergyVisualizerComponent::CalculateBondEnergy(float Wavelength) const
{
	if (Wavelength <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}
	return static_cast<float>((PlancksConstant * SpeedOfLight) / Wavelength);
}
