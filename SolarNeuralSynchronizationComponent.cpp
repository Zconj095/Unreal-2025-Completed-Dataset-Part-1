#include "SolarNeuralSynchronizationComponent.h"

#include "Math/UnrealMathUtility.h"

USolarNeuralSynchronizationComponent::USolarNeuralSynchronizationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarNeuralSynchronizationComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeElapsed = 0.0f;
}

void USolarNeuralSynchronizationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimeElapsed += DeltaTime;
    const float NeuralActivity = CalculateSolarNeuralActivity(TimeElapsed);

    UE_LOG(LogTemp, Log, TEXT("Time: %.2f s, Solar Neural Activity: %.4f"), TimeElapsed, NeuralActivity);
}

float USolarNeuralSynchronizationComponent::CalculateSolarNeuralActivity(float Time) const
{
    return N0 * (1.0f + Amplititude * FMath::Sin(OmegaS * Time + Phi));
}
