#include "ArboricortexComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UArboricortexComponent::UArboricortexComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UArboricortexComponent::BeginPlay()
{
	Super::BeginPlay();

	GenerateArboricortex();
}

void UArboricortexComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bLogFractalValue)
	{
		const float FractalValue = TreeFractalValue(RecursionDepth);
		UE_LOG(LogTemp, Log, TEXT("Tree Fractal Value at Depth %d: %0.2f"), RecursionDepth, FractalValue);
	}
}

float UArboricortexComponent::TreeFractalValue(int32 Depth) const
{
	if (Depth <= 0)
	{
		return 1.0f;
	}

	return TreeFractalValue(Depth - 1) + BranchingFactor * RateOfExpansion;
}

void UArboricortexComponent::GenerateArboricortex()
{
	if (!GetWorld())
	{
		return;
	}

	const FVector BasePosition = (GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector) + StartOffset;
	GenerateRecursiveBranch(BasePosition, RecursionDepth);
}

void UArboricortexComponent::GenerateRecursiveBranch(const FVector& Position, int32 Depth)
{
	if (Depth <= 0 || !GetWorld())
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Position, 25.0f, 12, FColor::Green, true, 10.0f);

	const int32 BranchCount = GetBranchCount();
	for (int32 Index = 0; Index < BranchCount; ++Index)
	{
		const float Angle = (360.0f / BranchCount) * Index;
		const FRotator Rotation(0.0f, Angle, 0.0f);
		const FVector Direction = Rotation.RotateVector(FVector::ForwardVector);
		const FVector NextPosition = Position + Direction * RateOfExpansion;

		DrawDebugLine(GetWorld(), Position, NextPosition, FColor::Yellow, true, 10.0f, 0, 2.0f);
		GenerateRecursiveBranch(NextPosition, Depth - 1);
	}
}

int32 UArboricortexComponent::GetBranchCount() const
{
	const int32 Rounded = FMath::Max(1, FMath::RoundToInt(BranchingFactor));
	return Rounded;
}
