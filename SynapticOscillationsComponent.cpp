#include "SynapticOscillationsComponent.h"
#include "Engine/World.h"

#include "Math/UnrealMathUtility.h"

USynapticOscillationsComponent::USynapticOscillationsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USynapticOscillationsComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USynapticOscillationsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    SynapticOscillation = CalculateOscillation(CurrentTime);
    UE_LOG(LogTemp, Log, TEXT("Synaptic Oscillation (S(t)): %.4f"), SynapticOscillation);
}

void USynapticOscillationsComponent::UpdateParameters(float NewAmplitude, float NewFrequency, float NewPhaseOffset)
{
    Amplitude = NewAmplitude;
    Frequency = NewFrequency;
    PhaseOffset = NewPhaseOffset;
}

float USynapticOscillationsComponent::CalculateOscillation(float Time) const
{
    const float AngularFrequency = 2.0f * PI * Frequency;
    return Amplitude * FMath::Sin(AngularFrequency * Time + PhaseOffset);
}
