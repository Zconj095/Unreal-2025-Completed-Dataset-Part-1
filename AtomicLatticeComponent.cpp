#include "AtomicLatticeComponent.h"
#include "Logging/LogMacros.h"

UAtomicLatticeComponent::UAtomicLatticeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAtomicLatticeComponent::BeginPlay()
{
	Super::BeginPlay();

	GeneratedLatticePoints = GenerateLatticePoints(DefaultRange);
	UE_LOG(LogTemp, Log, TEXT("Atomic lattice generated %d points using range %d."), GeneratedLatticePoints.Num(), DefaultRange);
}

FVector UAtomicLatticeComponent::CalculateLatticePoint(int32 N1, int32 N2, int32 N3) const
{
	return BasisVector1 * static_cast<float>(N1) +
		BasisVector2 * static_cast<float>(N2) +
		BasisVector3 * static_cast<float>(N3);
}

TArray<FVector> UAtomicLatticeComponent::GenerateLatticePoints(int32 Range) const
{
	TArray<FVector> Points;
	if (Range < 0)
	{
		return Points;
	}

	for (int32 N1 = -Range; N1 <= Range; ++N1)
	{
		for (int32 N2 = -Range; N2 <= Range; ++N2)
		{
			for (int32 N3 = -Range; N3 <= Range; ++N3)
			{
				Points.Add(CalculateLatticePoint(N1, N2, N3));
			}
		}
	}

	return Points;
}
