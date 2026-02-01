#include "CognitiveEvolutionPotentialComponent.h"

#include "Math/UnrealMathUtility.h"

UCognitiveEvolutionPotentialComponent::UCognitiveEvolutionPotentialComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveEvolutionPotentialComponent::BeginPlay()
{
	Super::BeginPlay();
	CEPValue = IntegrateCEP();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Evolution Potential (CEP): %.4f"), CEPValue);
}

float UCognitiveEvolutionPotentialComponent::IntegrateCEP() const
{
	const int32 Steps = FMath::Max(NumSteps, 1);
	const float DX = (XMax - XMin) / Steps;
	const float TimeSeconds = EndTime;

	float Sum = 0.0f;
	for (int32 Index = 0; Index < Steps; ++Index)
	{
		const float X = XMin + Index * DX;
		float Psi = WaveFunction(X, TimeSeconds);
		float PsiConj = ConjugateWaveFunction(X, TimeSeconds);
		Sum += PsiConj * Psi * DX;
	}

	return Sum;
}

float UCognitiveEvolutionPotentialComponent::WaveFunction(float X, float TimeSeconds) const
{
	return FMath::Sin(X + TimeSeconds);
}

float UCognitiveEvolutionPotentialComponent::ConjugateWaveFunction(float X, float TimeSeconds) const
{
	return FMath::Sin(X + TimeSeconds);
}
