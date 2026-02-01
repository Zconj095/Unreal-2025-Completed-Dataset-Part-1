#include "SynapticEnergyIntegrationComponent.h"

#include "Curves/CurveFloat.h"
#include "Engine/World.h"

USynapticEnergyIntegrationComponent::USynapticEnergyIntegrationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USynapticEnergyIntegrationComponent::BeginPlay()
{
    Super::BeginPlay();
    PreviousTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

void USynapticEnergyIntegrationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetWorld() || !EnergyFluxCurve)
    {
        return;
    }

    const float CurrentTime = GetWorld()->GetTimeSeconds();
    const float CurrentFlux = EnergyFluxCurve->GetFloatValue(CurrentTime);
    const float PreviousFlux = EnergyFluxCurve->GetFloatValue(PreviousTime);
    const float Delta = CurrentTime - PreviousTime;

    SynapticEnergy += FreeEnergyChange * (PreviousFlux + CurrentFlux) * 0.5f * Delta;
    PreviousTime = CurrentTime;

    UE_LOG(LogTemp, Log, TEXT("Synaptic Energy (En): %.2f"), SynapticEnergy);
}
