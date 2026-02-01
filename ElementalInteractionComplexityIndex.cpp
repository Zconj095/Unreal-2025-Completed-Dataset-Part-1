#include "ElementalInteractionComplexityIndex.h"
#include "Math/UnrealMathUtility.h"

AElementalInteractionComplexityIndex::AElementalInteractionComplexityIndex()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AElementalInteractionComplexityIndex::BeginPlay()
{
	Super::BeginPlay();

	if (Concentrations.Num() != InteractionPathwayLengths.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Concentrations and interaction pathway lengths must have matching lengths."));
		return;
	}

	const float EICI = CalculateEICI();
	UE_LOG(LogTemp, Log, TEXT("Elemental Interaction Complexity Index (EICI): %.4f"), EICI);
}

float AElementalInteractionComplexityIndex::CalculateEICI() const
{
	float Sum = 0.0f;
	for (int32 Index = 0; Index < Concentrations.Num(); ++Index)
	{
		const float Length = InteractionPathwayLengths[Index];
		if (Length <= 0.0f)
		{
			continue;
		}
		Sum += Concentrations[Index] * FMath::Log2(Length);
	}

	return Beta * Sum;
}
