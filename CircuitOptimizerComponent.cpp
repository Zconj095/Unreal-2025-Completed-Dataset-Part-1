#include "CircuitOptimizerComponent.h"

#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"

UCircuitOptimizerComponent::UCircuitOptimizerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCircuitOptimizerComponent::BeginPlay()
{
	Super::BeginPlay();

	OptimizedResult = OptimizeCircuit(100.0f, 1e-6f);
	UE_LOG(LogTemp, Log, TEXT("Circuit optimizer result: %.4f"), OptimizedResult);
}

float UCircuitOptimizerComponent::OptimizeCircuit(float InResistance, float InCapacitance)
{
	const float TargetFlux = DesiredFlux;
	const float Angular = 2.0f * PI * Frequency;

	// simple heuristic: flux ~ V/(sqrt(R^2 + (1/(ωC))^2))
	const float Reactance = 1.0f / (Angular * InCapacitance);
	const float Impedance = FMath::Sqrt(FMath::Square(InResistance) + FMath::Square(Reactance));
	const float Voltage = TargetFlux * Impedance;

	// adjust by scaling around desired flux
	const float Scaling = FMath::Clamp(TargetFlux / FMath::Max(Voltage, KINDA_SMALL_NUMBER), 0.1f, 5.0f);
	const float Result = Voltage * Scaling;

	OptimizedResult = Result;
	return Result;
}
