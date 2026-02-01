#include "CelestialObservationPotentialComponent.h"

#include "Curves/RichCurve.h"

UCelestialObservationPotentialComponent::UCelestialObservationPotentialComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCelestialObservationPotentialComponent::BeginPlay()
{
	Super::BeginPlay();

	const float ObservationPotential = CalculateObservationPotential();
	UE_LOG(LogTemp, Log, TEXT("Celestial Observation Potential (P_c): %.4f"), ObservationPotential);
}

float UCelestialObservationPotentialComponent::CalculateObservationPotential() const
{
	const int32 Steps = FMath::Max(IntegrationSteps, 1);
	const float Start = IntegrationStart;
	const float End = FMath::Max(IntegrationEnd, Start + KINDA_SMALL_NUMBER);
	const float Dx = (End - Start) / Steps;

	float Potential = 0.0f;
	FRichCurve* WaveCurve = const_cast<FRuntimeFloatCurve&>(WaveFunctionCurve).GetRichCurve();
	FRichCurve* Hamiltonian = const_cast<FRuntimeFloatCurve&>(HamiltonianCurve).GetRichCurve();

	if (!WaveCurve || !Hamiltonian)
	{
		UE_LOG(LogTemp, Warning, TEXT("Observation curves are missing RichCurve data."));
		return Potential;
	}

	for (int32 Index = 0; Index <= Steps; ++Index)
	{
		const float X = Start + Index * Dx;
		const float WaveValue = WaveCurve->Eval(X);
		const float HamiltonianValue = Hamiltonian->Eval(X);
		Potential += WaveValue * HamiltonianValue * Dx;
	}

	return Potential;
}
