#include "BiochemicalNetworkAdaptabilityComponent.h"
#include "Logging/LogMacros.h"

UBiochemicalNetworkAdaptabilityComponent::UBiochemicalNetworkAdaptabilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBiochemicalNetworkAdaptabilityComponent::BeginPlay()
{
	Super::BeginPlay();
	NetworkAdaptability = CalculateBNA(Lambda, DeltaNetwork, DeltaTime);
}

void UBiochemicalNetworkAdaptabilityComponent::TickComponent(float DeltaSeconds, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaSeconds, TickType, ThisTickFunction);
	if (FMath::IsNearlyZero(DeltaTime))
	{
		UE_LOG(LogTemp, Warning, TEXT("Δt must not be zero to calculate BNA."));
		return;
	}
	NetworkAdaptability = CalculateBNA(Lambda, DeltaNetwork, DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("BNA Result: %0.2f"), NetworkAdaptability);
}

float UBiochemicalNetworkAdaptabilityComponent::CalculateBNA(float LambdaValue, float DeltaNetworkValue, float DeltaTimeValue) const
{
	if (FMath::IsNearlyZero(DeltaTimeValue))
	{
		return 0.0f;
	}
	return LambdaValue * (DeltaNetworkValue / DeltaTimeValue);
}
