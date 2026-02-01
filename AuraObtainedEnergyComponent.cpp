#include "AuraObtainedEnergyComponent.h"

#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"

UAuraObtainedEnergyComponent::UAuraObtainedEnergyComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAuraObtainedEnergyComponent::BeginPlay()
{
    Super::BeginPlay();
    ApplyContentAura();
}

TArray<USceneComponent*> UAuraObtainedEnergyComponent::GetAllLayers() const
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

void UAuraObtainedEnergyComponent::ApplyContentAura()
{
    for (USceneComponent* Layer : GetAllLayers())
    {
        ApplyObtainedEnergyToAura(Layer);
    }
}

void UAuraObtainedEnergyComponent::ApplyObtainedEnergyToAura(USceneComponent* AuraLayer)
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

void UAuraObtainedEnergyComponent::ApplyToNiagara(UNiagaraComponent* NiagaraComp) const
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

void UAuraObtainedEnergyComponent::ApplyToCascade(UParticleSystemComponent* ParticleComp) const
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

