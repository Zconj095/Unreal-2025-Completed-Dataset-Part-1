#include "BiochemicalReactionSimulationComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalReactionSimulationComponent::UBiochemicalReactionSimulationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiochemicalReactionSimulationComponent::BeginPlay()
{
	Super::BeginPlay();

	ReactionSimulationPotential = CalculateBRSP();
	UE_LOG(LogTemp, Log, TEXT("Reaction Simulation Potential (Pr): %0.4f"), ReactionSimulationPotential);
}

float UBiochemicalReactionSimulationComponent::Hamiltonian(float X, float TimeSeconds) const
{
	return X * X + TimeSeconds * TimeSeconds;
}

float UBiochemicalReactionSimulationComponent::Wavefunction(float X, float TimeSeconds) const
{
	return FMath::Exp(-X * X - TimeSeconds * TimeSeconds);
}

float UBiochemicalReactionSimulationComponent::CalculateBRSP() const
{
	const float Dx = (EndTime - StartTime) / FMath::Max(NumSamples, 1);
	float Integral = 0.0f;

	for (int32 Index = 0; Index < NumSamples; ++Index)
	{
		const float X = StartTime + Index * Dx;
		const float CurrentTime = StartTime + Index * Dx;
		const float WaveConj = Wavefunction(X, CurrentTime);
		const float Wave = Wavefunction(X, CurrentTime);
		const float Hamilton = Hamiltonian(X, CurrentTime);
		Integral += WaveConj * Hamilton * Wave * Dx;
	}

	return Integral;
}
