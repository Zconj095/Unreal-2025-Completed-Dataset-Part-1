#include "DynamicSystemVisualizer.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"

ADynamicSystemVisualizer::ADynamicSystemVisualizer()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	VisualMesh->SetupAttachment(RootComponent);
}

void ADynamicSystemVisualizer::BeginPlay()
{
	Super::BeginPlay();

	if (Steps <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicSystemVisualizer requires at least one step."));
		return;
	}

	GenerateDisplacements();
	StepInterval = (SimulationTime > 0.0f) ? SimulationTime / Steps : 0.1f;
	TimeAccumulator = 0.0f;
	CurrentIndex = 0;
}

void ADynamicSystemVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Displacements.Num() == 0 || VisualMesh == nullptr || StepInterval <= 0.0f)
	{
		return;
	}

	TimeAccumulator += DeltaTime;

	while (TimeAccumulator >= StepInterval && CurrentIndex < Displacements.Num())
	{
		const float Displacement = Displacements[CurrentIndex];
		const FVector LocalPosition = FVector(0.0f, Displacement, 0.0f);
		VisualMesh->SetRelativeLocation(LocalPosition);
		++CurrentIndex;
		TimeAccumulator -= StepInterval;
	}
}

void ADynamicSystemVisualizer::GenerateDisplacements()
{
	const int32 ValidSteps = FMath::Max(1, Steps);
	const float DeltaT = (SimulationTime > 0.0f) ? SimulationTime / ValidSteps : 0.1f;
	const float Gamma = 2.0f * DampingRatio * NaturalFrequency;
	const float Stiffness = FMath::Square(NaturalFrequency);

	float Position = 0.0f;
	float Velocity = 0.0f;

	Displacements.SetNum(ValidSteps + 1);
	for (int32 Step = 0; Step <= ValidSteps; ++Step)
	{
		const float Time = Step * DeltaT;
		const float Force = FMath::Sin(2.0f * PI * ForceFrequency * Time);
		const float Acceleration = Force - Gamma * Velocity - Stiffness * Position;
		Velocity += Acceleration * DeltaT;
		Position += Velocity * DeltaT;
		Displacements[Step] = Position;
	}
}
