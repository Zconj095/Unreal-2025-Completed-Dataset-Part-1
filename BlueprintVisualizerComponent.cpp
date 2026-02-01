#include "BlueprintVisualizerComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBlueprintVisualizerComponent::UBlueprintVisualizerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBlueprintVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();

	const TArray<float> Blueprint = GenerateBlueprint();
	int32 Count = 0;
	for (float Value : Blueprint)
	{
		if (Value > VisualizationThreshold)
		{
			++Count;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Blueprint generated %d populated cells out of %d."), Count, Blueprint.Num());

	if (bDrawDebug)
	{
		DrawDebugVisualization(Blueprint);
	}
}

TArray<float> UBlueprintVisualizerComponent::GenerateBlueprint() const
{
	const int32 Size = FMath::Max(GridDimension, 1);
	TArray<float> Blueprint;
	Blueprint.Reserve(Size * Size * Size);

	for (int32 Z = 0; Z < Size; ++Z)
	{
		for (int32 Y = 0; Y < Size; ++Y)
		{
			for (int32 X = 0; X < Size; ++X)
			{
				Blueprint.Add(SampleValue(X, Y, Z));
			}
		}
	}

	return Blueprint;
}

float UBlueprintVisualizerComponent::SampleValue(int32 X, int32 Y, int32 Z) const
{
	const float Phase = X * 0.2f + Y * 0.3f + Z * 0.25f;
	const float Value = 0.5f + 0.5f * FMath::Sin(Phase) + 0.25f * FMath::Cos((Y + Z) * 0.1f);
	return FMath::Clamp(Value, 0.0f, 1.0f);
}

void UBlueprintVisualizerComponent::DrawDebugVisualization(const TArray<float>& Blueprint) const
{
	if (!GetWorld())
	{
		return;
	}

	const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
	const int32 Size = FMath::Max(GridDimension, 1);
	int32 Index = 0;

	for (int32 Z = 0; Z < Size; ++Z)
	{
		for (int32 Y = 0; Y < Size; ++Y)
		{
			for (int32 X = 0; X < Size; ++X, ++Index)
			{
				const float Value = Blueprint.IsValidIndex(Index) ? Blueprint[Index] : 0.0f;
				if (Value <= VisualizationThreshold)
				{
					continue;
				}

				const FVector Location = Origin + FVector(X * Spacing, Y * Spacing, Z * Spacing);
				DrawDebugBox(GetWorld(), Location, FVector(CubeSize), FColor::Cyan, true, 10.0f, 0, 2.0f);
			}
		}
	}
}
