#include "EmotionalBodyActor.h"

#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"

AEmotionalBodyActor::AEmotionalBodyActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Emotional Body"));
#endif
}

void AEmotionalBodyActor::BeginPlay()
{
    Super::BeginPlay();
    ApplyAuraSettings();
}

void AEmotionalBodyActor::ApplyAuraSettings()
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

void AEmotionalBodyActor::ApplyToNiagara(UNiagaraComponent* NiagaraComp) const
{
    if (!NiagaraComp)
    {
        return;
    }

    auto SetBothFloat = [NiagaraComp](const FName& Name, float Value)
    {
        NiagaraComp->SetVariableFloat(Name, Value);
        const FString UserPrefixed = FString::Printf(TEXT("User.%s"), *Name.ToString());
        NiagaraComp->SetVariableFloat(FName(*UserPrefixed), Value);
    };

    auto SetBothColor = [NiagaraComp](const FName& Name, const FLinearColor& Value)
    {
        NiagaraComp->SetVariableLinearColor(Name, Value);
        const FString UserPrefixed = FString::Printf(TEXT("User.%s"), *Name.ToString());
        NiagaraComp->SetVariableLinearColor(FName(*UserPrefixed), Value);
    };

    SetBothColor(AuraColorParam, AuraColor);
    SetBothFloat(AuraTransparencyParam, AuraTransparency);
    SetBothFloat(ParticleSizeParam, ParticleSize);
    SetBothFloat(ParticleCountParam, (float)ParticleCount);
    SetBothFloat(AuraRadiusParam, AuraRadius);
}

void AEmotionalBodyActor::ApplyToCascade(UParticleSystemComponent* ParticleComp) const
{
    if (!ParticleComp)
    {
        return;
    }

    ParticleComp->SetColorParameter(AuraColorParam, AuraColor.ToFColor(true));
    ParticleComp->SetFloatParameter(AuraTransparencyParam, AuraTransparency);
    ParticleComp->SetFloatParameter(ParticleSizeParam, ParticleSize);
    ParticleComp->SetFloatParameter(ParticleCountParam, (float)ParticleCount);
    ParticleComp->SetFloatParameter(AuraRadiusParam, AuraRadius);
}

