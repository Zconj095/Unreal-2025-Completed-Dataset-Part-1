#include "BiochemicalNetworkIntegrationComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiochemicalNetworkIntegrationComponent::UBiochemicalNetworkIntegrationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBiochemicalNetworkIntegrationComponent::BeginPlay()
{
	Super::BeginPlay();
	NetworkIntegration = CalculateBNI(Weights, Inputs);
}

void UBiochemicalNetworkIntegrationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	NetworkIntegration = CalculateBNI(Weights, Inputs);
	UE_LOG(LogTemp, Log, TEXT("Biochemical Network Integration (Ib): %0.2f"), NetworkIntegration);
}

float UBiochemicalNetworkIntegrationComponent::CalculateBNI(const TArray<float>& WeightArray, const TArray<float>& InputArray) const
{
	if (WeightArray.Num() != InputArray.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Weights and inputs arrays must have the same length."));
		return 0.0f;
	}

	float Result = 0.0f;
	for (int32 Index = 0; Index < WeightArray.Num(); ++Index)
	{
		Result += WeightArray[Index] * FMath::Loge(1.0f + InputArray[Index]);
	}
	return Result;
}
