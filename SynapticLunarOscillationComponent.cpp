#include "SynapticLunarOscillationComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticLunarOscillationComponent::USynapticLunarOscillationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USynapticLunarOscillationComponent::BeginPlay()
{
    Super::BeginPlay();
    ElapsedTime = 0.0f;
}

void USynapticLunarOscillationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    ElapsedTime += DeltaTime;
    OscillationValue = CalculateSLO(ElapsedTime);
    UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Synaptic Oscillation (S(t)): %.2f"), ElapsedTime, OscillationValue);
}

float USynapticLunarOscillationComponent::CalculateSLO(float Time) const
{
    return Amplitude * FMath::Sin(Frequency * Time + PhaseOffset);
}
