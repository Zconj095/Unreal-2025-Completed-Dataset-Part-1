#include "ChakraStoredEnergyComponent.h"

#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"

UChakraStoredEnergyComponent::UChakraStoredEnergyComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UChakraStoredEnergyComponent::BeginPlay()
{
    Super::BeginPlay();
    ApplyStoredEnergyToChakras();
}

TArray<USceneComponent*> UChakraStoredEnergyComponent::GetAllChakras() const
{
    TArray<USceneComponent*> Arr;
    Arr.Reserve(7);
    if (RootChakra) Arr.Add(RootChakra);
    if (SacralChakra) Arr.Add(SacralChakra);
    if (SolarPlexusChakra) Arr.Add(SolarPlexusChakra);
    if (HeartChakra) Arr.Add(HeartChakra);
    if (ThroatChakra) Arr.Add(ThroatChakra);
    if (ThirdEyeChakra) Arr.Add(ThirdEyeChakra);
    if (CrownChakra) Arr.Add(CrownChakra);
    return Arr;
}

void UChakraStoredEnergyComponent::ApplyStoredEnergyToChakras()
{
    for (USceneComponent* Layer : GetAllChakras())
    {
        ApplyStoredEnergyToChakra(Layer);
    }
}

void UChakraStoredEnergyComponent::ApplyStoredEnergyToChakra(USceneComponent* ChakraLayer)
{
    if (!ChakraLayer)
    {
        return;
    }

    if (UNiagaraComponent* NiagaraComp = Cast<UNiagaraComponent>(ChakraLayer))
    {
        ApplyToNiagara(NiagaraComp);
        return;
    }

    if (UParticleSystemComponent* ParticleComp = Cast<UParticleSystemComponent>(ChakraLayer))
    {
        ApplyToCascade(ParticleComp);
        return;
    }
}

void UChakraStoredEnergyComponent::ApplyToNiagara(UNiagaraComponent* NiagaraComp) const
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

void UChakraStoredEnergyComponent::ApplyToCascade(UParticleSystemComponent* ParticleComp) const
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

