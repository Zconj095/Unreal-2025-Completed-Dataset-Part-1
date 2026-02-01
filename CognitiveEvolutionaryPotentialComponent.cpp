#include "CognitiveEvolutionaryPotentialComponent.h"

#include "Math/UnrealMathUtility.h"

UCognitiveEvolutionaryPotentialComponent::UCognitiveEvolutionaryPotentialComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveEvolutionaryPotentialComponent::BeginPlay()
{
	Super::BeginPlay();
	CEPValue = CalculateCEP();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Evolutionary Potential (CEP): %.4f"), CEPValue);
}

float UCognitiveEvolutionaryPotentialComponent::CalculateCEP() const
{
	const int32 Steps = FMath::Max(NumSteps, 1);
	const float DX = (XMax - XMin) / Steps;
	const float TimeSeconds = EndTime;
	float Sum = 0.0f;

	for (int32 Index = 0; Index < Steps; ++Index)
	{
		const float X = XMin + Index * DX;
		const float Psi = WaveFunction(X, TimeSeconds);
		const float PsiConj = ConjugateWaveFunction(X, TimeSeconds);
		Sum += PsiConj * Psi * DX;
	}

	return Sum;
}

float UCognitiveEvolutionaryPotentialComponent::WaveFunction(float X, float TimeSeconds) const
{
	return FMath::Sin(X + TimeSeconds);
}

float UCognitiveEvolutionaryPotentialComponent::ConjugateWaveFunction(float X, float TimeSeconds) const
{
	return FMath::Sin(X + TimeSeconds);
}
