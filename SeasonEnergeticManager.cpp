#include "SeasonEnergeticManager.h"

#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"

ASeasonEnergeticManager::ASeasonEnergeticManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASeasonEnergeticManager::BeginPlay()
{
    Super::BeginPlay();

    ApplyChakraParticleBehavior();
    ApplyAuraParticleBehavior();
}

FSeasonParticleParams ASeasonEnergeticManager::GetChakraParamsForSeason(ESeason InSeason) const
{
    switch (InSeason)
    {
    case ESeason::Spring: return ChakraSpring;
    case ESeason::Summer: return ChakraSummer;
    case ESeason::Autumn: return ChakraAutumn;
    case ESeason::Winter: return ChakraWinter;
    default: return ChakraSpring;
    }
}

FSeasonParticleParams ASeasonEnergeticManager::GetAuraParamsForSeason(ESeason InSeason) const
{
    switch (InSeason)
    {
    case ESeason::Spring: return AuraSpring;
    case ESeason::Summer: return AuraSummer;
    case ESeason::Autumn: return AuraAutumn;
    case ESeason::Winter: return AuraWinter;
    default: return AuraSpring;
    }
}

void ASeasonEnergeticManager::ApplyChakraParticleBehavior()
{
    if (!ChakraRoot)
    {
        return;
    }
    const FSeasonParticleParams Params = GetChakraParamsForSeason(Season);
    ApplyParamsToRoot(ChakraRoot, Params);
}

void ASeasonEnergeticManager::ApplyAuraParticleBehavior()
{
    if (!AuraRoot)
    {
        return;
    }
    const FSeasonParticleParams Params = GetAuraParamsForSeason(Season);
    ApplyParamsToRoot(AuraRoot, Params);
}

void ASeasonEnergeticManager::ApplyParamsToRoot(USceneComponent* Root, const FSeasonParticleParams& Params) const
{
    if (!Root)
    {
        return;
    }

    // Apply to the root itself if it is a particle component
    if (UParticleSystemComponent* RootPSC = Cast<UParticleSystemComponent>(Root))
    {
        ApplyToCascade(RootPSC, Params);
    }
    if (UNiagaraComponent* RootNiagara = Cast<UNiagaraComponent>(Root))
    {
        ApplyToNiagara(RootNiagara, Params);
    }

    // Apply to all attached child components (Niagara or Cascade)
    TArray<USceneComponent*> ChildComponents;
    Root->GetChildrenComponents(true, ChildComponents);

    for (USceneComponent* Child : ChildComponents)
    {
        if (UParticleSystemComponent* PSC = Cast<UParticleSystemComponent>(Child))
        {
            ApplyToCascade(PSC, Params);
        }

        if (UNiagaraComponent* NiagaraComp = Cast<UNiagaraComponent>(Child))
        {
            ApplyToNiagara(NiagaraComp, Params);
        }
    }
}

void ASeasonEnergeticManager::ApplyToNiagara(UNiagaraComponent* NiagaraComp, const FSeasonParticleParams& Params) const
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

    SetBoth(SimulationSpeedParam, Params.SimulationSpeed);
    SetBoth(StartSizeParam, Params.StartSize);
    SetBoth(StartLifetimeParam, Params.StartLifetime);
    SetBoth(EmissionRateParam, Params.EmissionRate);
}

void ASeasonEnergeticManager::ApplyToCascade(UParticleSystemComponent* ParticleComp, const FSeasonParticleParams& Params) const
{
    if (!ParticleComp)
    {
        return;
    }
    ParticleComp->SetFloatParameter(SimulationSpeedParam, Params.SimulationSpeed);
    ParticleComp->SetFloatParameter(StartSizeParam, Params.StartSize);
    ParticleComp->SetFloatParameter(StartLifetimeParam, Params.StartLifetime);
    ParticleComp->SetFloatParameter(EmissionRateParam, Params.EmissionRate);
}
