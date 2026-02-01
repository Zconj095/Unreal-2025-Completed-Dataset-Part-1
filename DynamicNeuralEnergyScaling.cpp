#include "DynamicNeuralEnergyScaling.h"
#include "Engine/Engine.h"

ADynamicNeuralEnergyScaling::ADynamicNeuralEnergyScaling()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADynamicNeuralEnergyScaling::BeginPlay()
{
	Super::BeginPlay();

	ElapsedTime = 0.0f;
	NeuralEnergyCapacity = InitialEnergyCapacity;
}

void ADynamicNeuralEnergyScaling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MaxCapacity <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DynamicNeuralEnergyScaling requires MaxCapacity > 0."));
		return;
	}

	ElapsedTime += DeltaTime;
	NeuralEnergyCapacity = CalculateNeuralEnergyCapacity(ElapsedTime);
	UE_LOG(LogTemp, Log, TEXT("Elapsed Time: %.2f seconds"), ElapsedTime);
	UE_LOG(LogTemp, Log, TEXT("Neural Energy Capacity (N_e): %.2f"), NeuralEnergyCapacity);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, FString::Printf(TEXT("Elapsed Time: %.2f seconds"), ElapsedTime));
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("Neural Energy Capacity (N_e): %.2f"), NeuralEnergyCapacity));
	}
}

float ADynamicNeuralEnergyScaling::CalculateNeuralEnergyCapacity(float Elapsed) const
{
	const float ScalingFactor = 1.0f + (GrowthRate / MaxCapacity);
	return InitialEnergyCapacity * FMath::Pow(ScalingFactor, Elapsed);
}
