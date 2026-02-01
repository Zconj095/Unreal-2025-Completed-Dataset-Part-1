#include "AtomicEnergyFlowVisualizerComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAtomicEnergyFlowVisualizerComponent::UAtomicEnergyFlowVisualizerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtomicEnergyFlowVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
	VisualizeEnergyFlow();
}

float UAtomicEnergyFlowVisualizerComponent::CalculateEnergyInput(float EnthalpyChange) const
{
	const float ThermalLoss = EntropyChange * Temperature;
	return EnthalpyChange - ThermalLoss + MagicalEnergy;
}

void UAtomicEnergyFlowVisualizerComponent::VisualizeEnergyFlow()
{
	if (EnthalpyChanges.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AtomicEnergyFlowVisualizerComponent: No enthalpy data provided."));
		return;
	}

	const FVector BaseLocation = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
	for (int32 Index = 0; Index < EnthalpyChanges.Num(); ++Index)
	{
		const float EnergyInput = CalculateEnergyInput(EnthalpyChanges[Index]);
		const float Height = EnergyInput * ScaleFactor;
		const float HalfHeight = FMath::Max(1.f, FMath::Abs(Height) * 0.5f);

		UE_LOG(LogTemp, Log, TEXT("Enthalpy Change: %0.2f J, Energy Input: %0.2f J"), EnthalpyChanges[Index], EnergyInput);

		if (bDrawDebugBars && GetWorld())
		{
			const FVector BarCenter = BaseLocation + FVector(Index * BarSpacing, 0.0f, HalfHeight);
			const FVector Extents = FVector(BarSpacing * 0.25f, BarSpacing * 0.25f, HalfHeight);
			DrawDebugBox(GetWorld(), BarCenter, Extents, FColor::Cyan, false, DebugDuration, 0, 2.0f);
		}
	}
}
