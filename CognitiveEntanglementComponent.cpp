#include "CognitiveEntanglementComponent.h"

#include "Math/UnrealMathUtility.h"

UCognitiveEntanglementComponent::UCognitiveEntanglementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveEntanglementComponent::BeginPlay()
{
	Super::BeginPlay();
	CEPValue = CalculateCEP();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Entanglement Potential (CEP): %.5f"), CEPValue);
}

float UCognitiveEntanglementComponent::CalculateCEP() const
{
	const int32 Steps = FMath::Max(NumSteps, 1);
	const float DX = (XMax - XMin) / Steps;
	const float CurrentTime = EndTime;
	float Sum = 0.0f;

	for (int32 Index = 0; Index < Steps; ++Index)
	{
		const float X = XMin + Index * DX;
		const float Psi = WaveFunction(X, CurrentTime);
		const float PsiConj = ConjugateWaveFunction(X, CurrentTime);
		Sum += PsiConj * Psi * DX;
	}

	return Sum;
}

float UCognitiveEntanglementComponent::WaveFunction(float X, float TimeSeconds) const
{
	return FMath::Sin(X + TimeSeconds);
}

float UCognitiveEntanglementComponent::ConjugateWaveFunction(float X, float TimeSeconds) const
{
	return FMath::Sin(X + TimeSeconds);
}
