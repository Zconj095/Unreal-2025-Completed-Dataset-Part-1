#include "SolarEclipseNeuralSynchronizationComponent.h"

#include "Math/UnrealMathUtility.h"

USolarEclipseNeuralSynchronizationComponent::USolarEclipseNeuralSynchronizationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarEclipseNeuralSynchronizationComponent::BeginPlay()
{
    Super::BeginPlay();

    NeuralSynchronization = CalculateSENS(MoonShadowRadius, EclipseRange, EclipseEnergyFlux);
    UE_LOG(LogTemp, Log, TEXT("Neural Synchronization (Se): %.2f"), NeuralSynchronization);
}

void USolarEclipseNeuralSynchronizationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    NeuralSynchronization = CalculateSENS(MoonShadowRadius, EclipseRange, EclipseEnergyFlux);
    UE_LOG(LogTemp, Log, TEXT("Neural Synchronization (Se): %.2f"), NeuralSynchronization);
}

float USolarEclipseNeuralSynchronizationComponent::CalculateSENS(float Rm, float Rt, float Phi) const
{
    if (Rt <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Total solar eclipse range (Rt) must be greater than zero."));
        return 0.0f;
    }

    const float AngleFactor = FMath::Cos(PI * Rm / Rt);
    return AngleFactor * Phi;
}
