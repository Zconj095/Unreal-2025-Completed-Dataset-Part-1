#include "CognitiveDimensionalityComponent.h"

#include "Math/UnrealMathUtility.h"

UCognitiveDimensionalityComponent::UCognitiveDimensionalityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveDimensionalityComponent::BeginPlay()
{
	Super::BeginPlay();
	Dimensionality = CalculateDimensionality();
	UE_LOG(LogTemp, Log, TEXT("Cognitive Dimensionality (CD): %.4f"), Dimensionality);
}

float UCognitiveDimensionalityComponent::CalculateDimensionality() const
{
	if (TotalNeurons <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("Total neurons must be greater than zero."));
		return 0.0f;
	}

	const float Fraction = ActiveNeurons / TotalNeurons;
	return Delta * FMath::Loge(1.0f + Fraction) / FMath::Loge(2.0f);
}
