#include "AstronomicalEntropicEfficiencyComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAstronomicalEntropicEfficiencyComponent::UAstronomicalEntropicEfficiencyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAstronomicalEntropicEfficiencyComponent::BeginPlay()
{
	Super::BeginPlay();
	EntropicEfficiency = CalculateEfficiency(TotalInformationProcessed, NeuralEntropy);
}

void UAstronomicalEntropicEfficiencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	EntropicEfficiency = CalculateEfficiency(TotalInformationProcessed, NeuralEntropy);
	if (EntropicEfficiency <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Entropic efficiency could not be computed; check ΔS."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Entropic Efficiency (η_s): %0.4f"), EntropicEfficiency);
	}
}

float UAstronomicalEntropicEfficiencyComponent::CalculateEfficiency(float H, float DeltaS) const
{
	if (FMath::IsNearlyZero(DeltaS))
	{
		UE_LOG(LogTemp, Warning, TEXT("Neural entropy (ΔS) is zero; returning 0."));
		return 0.0f;
	}

	return H / DeltaS;
}

void UAstronomicalEntropicEfficiencyComponent::UpdateParameters(float NewTotalInformation, float NewNeuralEntropy)
{
	TotalInformationProcessed = NewTotalInformation;
	NeuralEntropy = NewNeuralEntropy;
	EntropicEfficiency = CalculateEfficiency(TotalInformationProcessed, NeuralEntropy);
}
