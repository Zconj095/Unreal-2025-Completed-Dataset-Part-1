#include "AuraBorrowedEnergyComponent.h"

#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"

UAuraBorrowedEnergyComponent::UAuraBorrowedEnergyComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAuraBorrowedEnergyComponent::BeginPlay()
{
    Super::BeginPlay();
    ApplyContentAura();
}

TArray<USceneComponent*> UAuraBorrowedEnergyComponent::GetAllLayers() const
{
    TArray<USceneComponent*> Layers;
    Layers.Reserve(7);
    if (EthericBody) Layers.Add(EthericBody);
    if (EmotionalBody) Layers.Add(EmotionalBody);
    if (MentalBody) Layers.Add(MentalBody);
    if (AstralBody) Layers.Add(AstralBody);
    if (EthericTemplate) Layers.Add(EthericTemplate);
    if (CelestialBody) Layers.Add(CelestialBody);
    if (CausalBody) Layers.Add(CausalBody);
    return Layers;
}

void UAuraBorrowedEnergyComponent::ApplyContentAura()
{
    for (USceneComponent* Layer : GetAllLayers())
    {
        ApplyBorrowedEnergyToAura(Layer);
    }
}

void UAuraBorrowedEnergyComponent::ApplyBorrowedEnergyToAura(USceneComponent* AuraLayer)
{
    if (!AuraLayer)
    {
        return;
    }

    if (UNiagaraComponent* NiagaraComp = Cast<UNiagaraComponent>(AuraLayer))
    {
        ApplyToNiagara(NiagaraComp);
        return;
    }

    if (UParticleSystemComponent* ParticleComp = Cast<UParticleSystemComponent>(AuraLayer))
    {
        ApplyToCascade(ParticleComp);
        return;
    }
}

void UAuraBorrowedEnergyComponent::ApplyToNiagara(UNiagaraComponent* NiagaraComp) const
{
    if (!NiagaraComp)
    {
        return;
    }

    auto SetBoth = [NiagaraComp](const FName& Name, float Value)
    {
        NiagaraComp->SetVariableFloat(Name, Value);
        const FString UserPrefixed = FString::Printf(TEXT("User.%s"), *Name.ToString());
        NiagaraComp->SetVariableFloat(FName(*UserPrefixed), Value);
    };

    SetBoth(SimulationSpeedParam, SimulationSpeed);
    SetBoth(StartSizeParam, StartSize);
    SetBoth(StartLifetimeParam, StartLifetime);
    SetBoth(RateOverTimeParam, RateOverTime);
}

void UAuraBorrowedEnergyComponent::ApplyToCascade(UParticleSystemComponent* ParticleComp) const
{
    if (!ParticleComp)
    {
        return;
    }

    ParticleComp->SetFloatParameter(SimulationSpeedParam, SimulationSpeed);
    ParticleComp->SetFloatParameter(StartSizeParam, StartSize);
    ParticleComp->SetFloatParameter(StartLifetimeParam, StartLifetime);
    ParticleComp->SetFloatParameter(RateOverTimeParam, RateOverTime);
}

