#include "CelestialMotionComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

UCelestialMotionComponent::UCelestialMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCelestialMotionComponent::BeginPlay()
{
	Super::BeginPlay();

	OrbitPoints.Reset();
	const float EffectiveNodes = FMath::Max(NumPoints, 3);
	for (int32 Index = 0; Index < EffectiveNodes; ++Index)
	{
		const float Theta = 2.0f * PI * Index / EffectiveNodes;
		const float Distance = CalculateOrbitalDistance(Theta, SemiMajorAxis, Eccentricity);
		const FVector Location = FVector(Distance * FMath::Cos(Theta), Distance * FMath::Sin(Theta), 0.0f) + GetOwner()->GetActorLocation();
		OrbitPoints.Add(Location);
		DrawDebugSphere(GetWorld(), Location, 5.0f, 8, FColor::Cyan, false, 10.0f);
	}

	UE_LOG(LogTemp, Log, TEXT("Generated %d orbit points."), OrbitPoints.Num());
}

float UCelestialMotionComponent::CalculateOrbitalDistance(float Theta, float SemiMajor, float EccentricityValue) const
{
	if (EccentricityValue < 0.0f || EccentricityValue >= 1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Eccentricity must be between 0 and 1."));
		return 0.0f;
	}

	const float Numerator = SemiMajor * (1.0f - FMath::Square(EccentricityValue));
	const float Denominator = 1.0f + EccentricityValue * FMath::Cos(Theta);
	if (FMath::IsNearlyZero(Denominator))
	{
		return 0.0f;
	}
	return Numerator / Denominator;
}
