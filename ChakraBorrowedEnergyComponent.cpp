#include "ChakraBorrowedEnergyComponent.h"

#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"

UChakraBorrowedEnergyComponent::UChakraBorrowedEnergyComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UChakraBorrowedEnergyComponent::BeginPlay()
{
    Super::BeginPlay();
    ApplyBorrowedEnergyToChakras();
}

TArray<USceneComponent*> UChakraBorrowedEnergyComponent::GetAllChakras() const
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

void UChakraBorrowedEnergyComponent::ApplyBorrowedEnergyToChakras()
{
    for (USceneComponent* Layer : GetAllChakras())
    {
        ApplyBorrowedEnergyToChakra(Layer);
    }
}

void UChakraBorrowedEnergyComponent::ApplyBorrowedEnergyToChakra(USceneComponent* ChakraLayer)
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

void UChakraBorrowedEnergyComponent::ApplyToNiagara(UNiagaraComponent* NiagaraComp) const
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

void UChakraBorrowedEnergyComponent::ApplyToCascade(UParticleSystemComponent* ParticleComp) const
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

