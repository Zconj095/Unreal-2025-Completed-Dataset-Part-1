#include "SynapticEnergyOscillationsComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticEnergyOscillationsComponent::USynapticEnergyOscillationsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USynapticEnergyOscillationsComponent::BeginPlay()
{
    Super::BeginPlay();
    ElapsedTime = 0.0f;
}

void USynapticEnergyOscillationsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    ElapsedTime += DeltaTime;
    SynapticEnergy = CalculateSynapticEnergy(ElapsedTime);
    UE_LOG(LogTemp, Log, TEXT("Elapsed Time: %.2f seconds, Synaptic Energy (S(t)): %.2f"), ElapsedTime, SynapticEnergy);
}

float USynapticEnergyOscillationsComponent::CalculateSynapticEnergy(float Time) const
{
    const float AngularFrequency = 2.0f * PI * Frequency;
    return Amplitude * FMath::Sin(AngularFrequency * Time + PhaseOffset);
}
