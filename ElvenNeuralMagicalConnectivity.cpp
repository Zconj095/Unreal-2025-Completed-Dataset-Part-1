#include "ElvenNeuralMagicalConnectivity.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

AElvenNeuralMagicalConnectivity::AElvenNeuralMagicalConnectivity()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	SignalSpline = CreateDefaultSubobject<USplineComponent>(TEXT("SignalSpline"));
	SignalSpline->SetupAttachment(RootComponent);
	SignalSpline->bDrawDebug = false;
}

void AElvenNeuralMagicalConnectivity::BeginPlay()
{
	Super::BeginPlay();

	if (TimeStep <= 0.0f || SimulationTime <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("ElvenNeuralMagicalConnectivity requires positive SimulationTime and TimeStep."));
		return;
	}

	ElapsedTime = 0.0f;
	SimulationPoints.Empty();
	SignalSpline->ClearSplinePoints(false);

	SimulateSignal();
	SpawnDebugPoints();
}

void AElvenNeuralMagicalConnectivity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetWorld())
	{
		return;
	}

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	const float SignalIntensity = CalculateSignalIntensity(CurrentTime);
	UE_LOG(LogTemp, Log, TEXT("Real-Time Signal Intensity: %.2f"), SignalIntensity);
}

void AElvenNeuralMagicalConnectivity::SimulateSignal()
{
	int32 Index = 0;
	float Time = 0.0f;

	while (Time <= SimulationTime)
	{
		const float SignalIntensity = CalculateSignalIntensity(Time);
		UE_LOG(LogTemp, Log, TEXT("Time: %.2fs, Signal Intensity: %.2f"), Time, SignalIntensity);

		const FVector Point(Time * 100.0f, SignalIntensity * 10.0f, 0.0f);
		SimulationPoints.Add(Point);
		SignalSpline->AddSplinePoint(Point, ESplineCoordinateSpace::Local, false);

		Time += TimeStep;
		++Index;
	}

	SignalSpline->UpdateSpline();
}

float AElvenNeuralMagicalConnectivity::CalculateSignalIntensity(float TimeSeconds) const
{
	const float NeuralComponent = AmplitudeA * FMath::Exp(ManaAmplificationFactor * TimeSeconds);
	const float MagicalComponent = AmplitudeB * FMath::Cos(Frequency * TimeSeconds);
	return NeuralComponent + MagicalComponent;
}

void AElvenNeuralMagicalConnectivity::SpawnDebugPoints() const
{
	if (SimulationPoints.Num() < 2)
	{
		return;
	}

	for (int32 Index = 0; Index < SimulationPoints.Num() - 1; ++Index)
	{
		const FVector Start = GetActorLocation() + SimulationPoints[Index];
		const FVector End = GetActorLocation() + SimulationPoints[Index + 1];
		DrawDebugLine(GetWorld(), Start, End, LineColor, false, SimulationTime + 1.0f, 0, LineWidth);
	}
}
