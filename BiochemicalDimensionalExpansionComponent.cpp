#include "BiochemicalDimensionalExpansionComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalDimensionalExpansionComponent::UBiochemicalDimensionalExpansionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBiochemicalDimensionalExpansionComponent::BeginPlay()
{
	Super::BeginPlay();
	BDEResult = CalculateBDE(Theta, NeuronCount, Dimensionality, ConnectivityDensity);
}

void UBiochemicalDimensionalExpansionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	BDEResult = CalculateBDE(Theta, NeuronCount, Dimensionality, ConnectivityDensity);
	if (bLogResult)
	{
		UE_LOG(LogTemp, Log, TEXT("BDE Result: %0.2f"), BDEResult);
	}
}

float UBiochemicalDimensionalExpansionComponent::CalculateBDE(float ThetaValue, float NeuronCountValue, float DimensionalityValue, float ConnectivityValue) const
{
	if (ConnectivityValue <= -1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Connectivity density must be greater than -1."));
		return 0.0f;
	}

	const float Growth = FMath::Pow(NeuronCountValue, DimensionalityValue);
	const float LogValue = FMath::Log2(1.0f + ConnectivityValue);
	return ThetaValue * Growth * LogValue;
}
