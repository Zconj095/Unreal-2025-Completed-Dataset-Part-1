#include "HybridAdaptationRateComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

UHybridAdaptationRateComponent::UHybridAdaptationRateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHybridAdaptationRateComponent::BeginPlay()
{
	Super::BeginPlay();
	RecalculateAdaptation();
}

void UHybridAdaptationRateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDrawDebugGizmos)
	{
		DrawAdaptationGizmos();
	}
}

void UHybridAdaptationRateComponent::CalculateAdaptationCurve()
{
	const int32 ClampedSteps = FMath::Max(1, TotalSteps);
	AdaptationCurve.SetNum(ClampedSteps);

	for (int32 Index = 0; Index < ClampedSteps; ++Index)
	{
		const float Time = Index * TimeStep;
		AdaptationCurve[Index] = InitialAdaptability * FMath::Exp(-DecayRate * Time) + EnergyGradient;
	}
}

void UHybridAdaptationRateComponent::LogAdaptationCurve() const
{
	for (int32 Index = 0; Index < AdaptationCurve.Num(); ++Index)
	{
		const float Time = Index * TimeStep;
		UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Adaptation Rate A(t): %.4f"), Time, AdaptationCurve[Index]);
	}
}

void UHybridAdaptationRateComponent::TensorFlowValidation() const
{
	if (AdaptationCurve.Num() == 0)
	{
		return;
	}

	for (int32 Index = 0; Index < AdaptationCurve.Num(); ++Index)
	{
		const float Time = Index * TimeStep;
		const float ValidationValue = InitialAdaptability * FMath::Exp(-DecayRate * Time) + EnergyGradient;
		UE_LOG(LogTemp, Log, TEXT("[TensorFlow] Time: %.2f, Adaptation Rate A(t): %.4f"), Time, ValidationValue);
	}
}

void UHybridAdaptationRateComponent::DrawAdaptationGizmos() const
{
	if (!GetWorld() || AdaptationCurve.Num() == 0)
	{
		return;
	}

	const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

	for (int32 Index = 0; Index < AdaptationCurve.Num(); ++Index)
	{
		const float Time = Index * TimeStep;
		const float Value = AdaptationCurve[Index];
		const FVector Location = Origin + FVector(Time, Value, 0.0f);
		DrawDebugSphere(GetWorld(), Location, 2.0f, 8, FColor::Red, false, 0.0f, 0, 1.5f);
	}
}

void UHybridAdaptationRateComponent::RecalculateAdaptation()
{
	CalculateAdaptationCurve();
	LogAdaptationCurve();
	TensorFlowValidation();
}

const TArray<float>& UHybridAdaptationRateComponent::GetAdaptationCurve() const
{
	return AdaptationCurve;
}
