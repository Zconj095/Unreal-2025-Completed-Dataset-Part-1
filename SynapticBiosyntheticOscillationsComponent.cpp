#include "SynapticBiosyntheticOscillationsComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticBiosyntheticOscillationsComponent::USynapticBiosyntheticOscillationsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USynapticBiosyntheticOscillationsComponent::BeginPlay()
{
    Super::BeginPlay();
    ElapsedTime = 0.0f;
}

void USynapticBiosyntheticOscillationsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    ElapsedTime += DeltaTime;
    OscillationValue = CalculateOscillation(ElapsedTime);
    UE_LOG(LogTemp, Log, TEXT("Synaptic Biosynthetic Oscillation (S(t)) at time %.2f: %.4f"), ElapsedTime, OscillationValue);
}

float USynapticBiosyntheticOscillationsComponent::CalculateOscillation(float Time) const
{
    const float AngularFrequency = 2.0f * PI * Frequency;
    return Amplitude * FMath::Sin(AngularFrequency * Time + PhaseOffset);
}
