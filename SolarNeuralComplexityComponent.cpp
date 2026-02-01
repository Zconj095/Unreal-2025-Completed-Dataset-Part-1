#include "SolarNeuralComplexityComponent.h"

#include "Math/UnrealMathUtility.h"

USolarNeuralComplexityComponent::USolarNeuralComplexityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarNeuralComplexityComponent::BeginPlay()
{
    Super::BeginPlay();
    TimeElapsed = 0.0f;
}

void USolarNeuralComplexityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    TimeElapsed += DeltaTime;
    SolarComplexity = CalculateSNC(InitialComplexity, GrowthRate, TimeElapsed);
    UE_LOG(LogTemp, Log, TEXT("Time: %.2f, Solar Neural Complexity (Cs(t)): %.2f"), TimeElapsed, SolarComplexity);
}

float USolarNeuralComplexityComponent::CalculateSNC(float Complexity, float Rate, float Time) const
{
    return Complexity * FMath::Exp(Rate * Time);
}
