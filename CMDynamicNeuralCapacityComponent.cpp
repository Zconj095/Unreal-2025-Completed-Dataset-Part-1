#include "CMDynamicNeuralCapacityComponent.h"
#include "Engine/World.h"

UCMDynamicNeuralCapacityComponent::UCMDynamicNeuralCapacityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCMDynamicNeuralCapacityComponent::BeginPlay()
{
	Super::BeginPlay();
	NeuralCapacity = CalculateCurrentCapacity();
}

void UCMDynamicNeuralCapacityComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	NeuralCapacity = CalculateCurrentCapacity();
	const float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Log, TEXT("Neural Capacity (N_a) at time %.2f: %.4f"), Time, NeuralCapacity);
}

float UCMDynamicNeuralCapacityComponent::CalculateCurrentCapacity() const
{
	const float Ratio = 1.0f + (GrowthRate / FMath::Max(MaxCapacity, KINDA_SMALL_NUMBER));
	return InitialCapacity * FMath::Pow(Ratio, GetWorld()->GetTimeSeconds());
}
