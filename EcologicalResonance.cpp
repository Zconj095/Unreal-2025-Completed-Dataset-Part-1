#include "EcologicalResonance.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

AEcologicalResonance::AEcologicalResonance()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEcologicalResonance::BeginPlay()
{
	Super::BeginPlay();

	if (OscillatorCount <= 0 || TimeStep <= 0.0f || SimulationDuration <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("EcologicalResonance requires positive oscillator count, time step, and simulation duration."));
		SetActorTickEnabled(false);
		return;
	}

	InitializeOscillators();
	TimeAccumulator = 0.0f;
	ElapsedTime = 0.0f;
	bSimulationComplete = false;
	bGraphDrawn = false;
}

void AEcologicalResonance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSimulationComplete)
	{
		return;
	}

	TimeAccumulator += DeltaTime;
	while (TimeAccumulator >= TimeStep && !bSimulationComplete)
	{
		StepSimulation();
		TimeAccumulator -= TimeStep;
	}

	if (bLogSynchronization && Phases.Num() > 0)
	{
		const float Synchronization = CalculateSynchronization();
		UE_LOG(LogTemp, Log, TEXT("Current Phase Synchronization: %.2f"), Synchronization);
	}
}

void AEcologicalResonance::InitializeOscillators()
{
	Phases.SetNumZeroed(OscillatorCount);
	NaturalFrequencies.SetNumZeroed(OscillatorCount);
	PhaseHistory.Empty();

	for (int32 Index = 0; Index < OscillatorCount; ++Index)
	{
		Phases[Index] = FMath::FRandRange(0.0f, 2.0f * PI);
		NaturalFrequencies[Index] = FMath::FRandRange(-1.0f, 1.0f);
	}
}

void AEcologicalResonance::StepSimulation()
{
	if (Phases.Num() == 0)
	{
		return;
	}

	TArray<float> Derivatives = ComputePhaseDerivatives();
	for (int32 Index = 0; Index < OscillatorCount; ++Index)
	{
		Phases[Index] += TimeStep * Derivatives[Index];
	}

	PhaseHistory.Add(Phases);
	ElapsedTime += TimeStep;

	if (ElapsedTime >= SimulationDuration)
	{
		bSimulationComplete = true;
		if (bDrawDebugGraph && !bGraphDrawn)
		{
			VisualizeResonance();
			bGraphDrawn = true;
		}
	}
}

TArray<float> AEcologicalResonance::ComputePhaseDerivatives() const
{
	TArray<float> Derivatives;
	Derivatives.SetNumZeroed(OscillatorCount);

	for (int32 Index = 0; Index < OscillatorCount; ++Index)
	{
		float SumSin = 0.0f;
		for (int32 Other = 0; Other < OscillatorCount; ++Other)
		{
			SumSin += FMath::Sin(Phases[Other] - Phases[Index]);
		}

		const float CouplingTerm = (CouplingStrength / OscillatorCount) * SumSin;
		const float ManaTerm = ManaAmplification * FMath::Sin(Phases[Index]);
		Derivatives[Index] = NaturalFrequencies[Index] + CouplingTerm + ManaTerm;
	}

	return Derivatives;
}

float AEcologicalResonance::CalculateSynchronization() const
{
	if (Phases.Num() == 0)
	{
		return 0.0f;
	}

	float SumCos = 0.0f;
	float SumSin = 0.0f;

	for (int32 Index = 0; Index < OscillatorCount; ++Index)
	{
		SumCos += FMath::Cos(Phases[Index]);
		SumSin += FMath::Sin(Phases[Index]);
	}

	const float Magnitude = FMath::Sqrt(SumCos * SumCos + SumSin * SumSin);
	return Magnitude / OscillatorCount;
}

void AEcologicalResonance::VisualizeResonance()
{
	if (!GetWorld() || PhaseHistory.Num() == 0)
	{
		return;
	}

	const float Duration = 30.0f;
	const float HeightScale = GraphSpacing * 0.1f;

	for (int32 Oscillator = 0; Oscillator < OscillatorCount; ++Oscillator)
	{
		for (int32 TimeIndex = 0; TimeIndex < PhaseHistory.Num() - 1; ++TimeIndex)
		{
			const float X0 = TimeIndex * TimeStep;
			const float X1 = (TimeIndex + 1) * TimeStep;
			const float Y0 = FMath::Sin(PhaseHistory[TimeIndex][Oscillator]) * HeightScale;
			const float Y1 = FMath::Sin(PhaseHistory[TimeIndex + 1][Oscillator]) * HeightScale;
			const float ZOffset = Oscillator * GraphSpacing;

			const FVector Start(X0, ZOffset, Y0);
			const FVector End(X1, ZOffset, Y1);
			DrawDebugLine(GetWorld(), Start, End, FColor::MakeRandomColor(), false, Duration, 0, 1.0f);
		}
	}
}
