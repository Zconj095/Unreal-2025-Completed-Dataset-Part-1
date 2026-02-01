#include "AethericSynapseTransmissionComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAethericSynapseTransmissionComponent::UAethericSynapseTransmissionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAethericSynapseTransmissionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAethericSynapseTransmissionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float Probability = CalculateSynapseTransmission(MagicInput, ScienceInput, Alpha, Beta);
	UE_LOG(LogTemp, Log, TEXT("Synaptic Transmission Probability: %0.4f"), Probability);
}

float UAethericSynapseTransmissionComponent::CalculateSynapseTransmission(float Magic, float Science, float AlphaValue, float BetaValue) const
{
	const float SumOfSquares = Magic * Magic + Science * Science;
	const float Exponent = -BetaValue * SumOfSquares;
	return AlphaValue * FMath::Exp(Exponent);
}
