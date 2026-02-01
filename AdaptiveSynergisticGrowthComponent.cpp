#include "AdaptiveSynergisticGrowthComponent.h"
#include "Logging/LogMacros.h"

UAdaptiveSynergisticGrowthComponent::UAdaptiveSynergisticGrowthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAdaptiveSynergisticGrowthComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	GenerateGrowthSamples();
}

void UAdaptiveSynergisticGrowthComponent::BeginPlay()
{
	Super::BeginPlay();

	GenerateGrowthSamples();
	const TArray<float>& Samples = CalculateSynergisticGrowth();
	for (int32 Index = 0; Index < Samples.Num(); ++Index)
	{
		const float Time = FMath::Lerp(StartTime, EndTime, static_cast<float>(Index) / FMath::Max(Resolution - 1, 1));
		UE_LOG(LogTemp, Log, TEXT("Time: %0.2f, Growth: %0.4f"), Time, Samples[Index]);
	}

	LogTensorFlowValidation();
}

void UAdaptiveSynergisticGrowthComponent::GenerateGrowthSamples()
{
	GrowthSamples.Reset();
	GrowthSamples.Reserve(Resolution);

	const float EnergySum = BiologicalEnergy + MagicalEnergy;
	const float GrowthValue = InitialGrowthRate * FMath::Exp(GrowthConstant * EnergySum);

	for (int32 Index = 0; Index < Resolution; ++Index)
	{
		GrowthSamples.Add(GrowthValue);
	}
}

const TArray<float>& UAdaptiveSynergisticGrowthComponent::CalculateSynergisticGrowth()
{
	if (Resolution <= 0)
	{
		Resolution = 1;
	}

	if (GrowthSamples.Num() != Resolution)
	{
		GenerateGrowthSamples();
	}

	return GrowthSamples;
}

void UAdaptiveSynergisticGrowthComponent::LogTensorFlowValidation() const
{
	const float EnergySum = BiologicalEnergy + MagicalEnergy;
	const float GrowthValue = InitialGrowthRate * FMath::Exp(GrowthConstant * EnergySum);
	for (int32 Index = 0; Index < Resolution; ++Index)
	{
		const float Time = FMath::Lerp(StartTime, EndTime, static_cast<float>(Index) / FMath::Max(Resolution - 1, 1));
		UE_LOG(LogTemp, Log, TEXT("TensorFlow Placeholder - Time: %0.2f, Growth: %0.4f"), Time, GrowthValue);
	}
}
