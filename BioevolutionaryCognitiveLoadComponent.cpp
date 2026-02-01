#include "BioevolutionaryCognitiveLoadComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBioevolutionaryCognitiveLoadComponent::UBioevolutionaryCognitiveLoadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBioevolutionaryCognitiveLoadComponent::BeginPlay()
{
	Super::BeginPlay();

	CognitiveLoad = CalculateCognitiveLoad(EnvironmentalStimuli, GeneticStimuli, TimeConstant, StartTime, EndTime, IntegrationSteps);
	UE_LOG(LogTemp, Log, TEXT("Bioevolutionary Cognitive Load (L): %0.4f"), CognitiveLoad);
}

float UBioevolutionaryCognitiveLoadComponent::CalculateCognitiveLoad(float Environmental, float Genetic, float Tau, float Start, float End, int32 Steps) const
{
	if (Tau <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time constant must be greater than zero."));
		return 0.0f;
	}

	const float Dt = (End - Start) / FMath::Max(Steps, 1);
	float Sum = 0.0f;

	for (int32 Index = 0; Index < Steps; ++Index)
	{
		const float CurrentTime = Start + Index * Dt;
		const float Stimuli = StimuliFunction(Environmental, Genetic, CurrentTime);
		Sum += Stimuli * Dt;
	}

	return Sum / Tau;
}

float UBioevolutionaryCognitiveLoadComponent::StimuliFunction(float Environmental, float Genetic, float TimeSeconds) const
{
	return Environmental * FMath::Sin(TimeSeconds) + Genetic * FMath::Cos(TimeSeconds);
}
