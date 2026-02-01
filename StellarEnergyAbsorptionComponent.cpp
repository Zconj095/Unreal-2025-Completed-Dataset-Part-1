#include "StellarEnergyAbsorptionComponent.h"

#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

UStellarEnergyAbsorptionComponent::UStellarEnergyAbsorptionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UStellarEnergyAbsorptionComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentTime = 0.0f;
    AbsorbedEnergy = 0.0f;
}

void UStellarEnergyAbsorptionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentTime += DeltaTime;

    if (CurrentTime <= ObservationInterval)
    {
        const float Flux = CalculateFlux(CurrentTime);
        AbsorbedEnergy += Efficiency * Flux * DeltaTime;
    }
    else
    {
        LogFinalEnergy();
        SetComponentTickEnabled(false);
    }
}

float UStellarEnergyAbsorptionComponent::CalculateFlux(float Time) const
{
    return FMath::Sin(Time) + 1.0f;
}

void UStellarEnergyAbsorptionComponent::LogFinalEnergy() const
{
    UE_LOG(LogTemp, Log, TEXT("Total Absorbed Energy after %.2f seconds: %.4f"), ObservationInterval, AbsorbedEnergy);
}
