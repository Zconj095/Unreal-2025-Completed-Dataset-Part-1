#include "BiochemicalReactionSimulation2Component.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalReactionSimulation2Component::UBiochemicalReactionSimulation2Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiochemicalReactionSimulation2Component::BeginPlay()
{
	Super::BeginPlay();

	ReactionSimulationPotential = CalculateBRSP();
	UE_LOG(LogTemp, Log, TEXT("Reaction Simulation Potential (Pr): %0.4f"), ReactionSimulationPotential);
}

float UBiochemicalReactionSimulation2Component::Hamiltonian(float X, float TimeSeconds) const
{
	return X * X + TimeSeconds * TimeSeconds;
}

float UBiochemicalReactionSimulation2Component::Wavefunction(float X, float TimeSeconds) const
{
	return FMath::Exp(-X * X - TimeSeconds * TimeSeconds);
}

float UBiochemicalReactionSimulation2Component::CalculateBRSP() const
{
	const float Dx = (EndTime - StartTime) / FMath::Max(NumSamples, 1);
	float Integral = 0.0f;

	for (int32 SampleIndex = 0; SampleIndex < NumSamples; ++SampleIndex)
	{
		const float X = StartTime + SampleIndex * Dx;
		const float CurrentTime = StartTime + SampleIndex * Dx;
		const float WaveConj = Wavefunction(X, CurrentTime);
		const float Wave = Wavefunction(X, CurrentTime);
		const float Hamilton = Hamiltonian(X, CurrentTime);
		Integral += WaveConj * Hamilton * Wave * Dx;
	}

	return Integral;
}
