#include "SolarEnergyIntegrationComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

USolarEnergyIntegrationComponent::USolarEnergyIntegrationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarEnergyIntegrationComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USolarEnergyIntegrationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentTime += DeltaTime;
    SolarEnergyIntegrated = CalculateSEI(InitialTime, CurrentTime, TimeStep, EnvironmentParameter);
    UE_LOG(LogTemp, Log, TEXT("Solar Energy Integrated (Es): %.2f"), SolarEnergyIntegrated);
}

float USolarEnergyIntegrationComponent::CalculateSEI(float Start, float End, float Delta, float Parameter) const
{
    if (Delta <= 0.0f || End <= Start)
    {
        return 0.0f;
    }

    float Sum = 0.0f;
    for (float Time = Start; Time < End; Time += Delta)
    {
        const float Flux = SolarEnergyFlux(Parameter, Time);
        Sum += Flux * Delta;
    }

    return Sum;
}

float USolarEnergyIntegrationComponent::SolarEnergyFlux(float Parameter, float Time) const
{
    return Parameter * FMath::Sin(2.0f * PI * Time);
}
