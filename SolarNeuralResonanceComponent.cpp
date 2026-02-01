#include "SolarNeuralResonanceComponent.h"

#include "Math/UnrealMathUtility.h"

USolarNeuralResonanceComponent::USolarNeuralResonanceComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarNeuralResonanceComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeElapsed = 0.0f;
}

void USolarNeuralResonanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimeElapsed += DeltaTime;
    const float PsiSolar = CalculateSolarNeuralResonance(TimeElapsed);
    UE_LOG(LogTemp, Log, TEXT("ψ_solar(t) at t=%.2fs: %.4f"), TimeElapsed, PsiSolar);
}

float USolarNeuralResonanceComponent::CalculateSolarNeuralResonance(float Time) const
{
    const float SolarWave = Gamma * FMath::Cos(2.0f * PI * FSolar * Time);
    const float RadiantFlux = Lambda * CalculateRadiantFlux(Time);
    return SolarWave + RadiantFlux;
}

float USolarNeuralResonanceComponent::CalculateRadiantFlux(float Time) const
{
    return EFluxBase * (1.0f + FMath::Sin(Time));
}
