// Converted from Unity MonoBehaviour FluctLightBehavior to Unreal ActorComponent.
#include "FluctLightComponent.h"

#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

UFluctLightComponent::UFluctLightComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UFluctLightComponent::BeginPlay()
{
    Super::BeginPlay();

    UpdateVisuals(CurrentFluctLight.BaseColor, CurrentFluctLight.EmotionalIntensity * 2.0f);
}

void UFluctLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!LightAura)
    {
        return;
    }

    SimulatePulsing(DeltaTime);
}

void UFluctLightComponent::SimulatePulsing(float DeltaTime)
{
    if (!LightAura)
    {
        return;
    }

    const float Range = CurrentFluctLight.EmotionalIntensity * 3.0f;
    const float Time = GetWorld() ? GetWorld()->GetTimeSeconds() * PulseSpeed : 0.0f;
    const float Intensity = Range - FMath::Abs(FMath::Fmod(Time, Range * 2.0f) - Range);
    ApplyIntensityToLight(Intensity);
}

void UFluctLightComponent::ActivateLight()
{
    bIsActive = true;
    UpdateVisuals(CurrentFluctLight.ActiveColor, CurrentFluctLight.EmotionalIntensity * 4.0f);
}

void UFluctLightComponent::DeactivateLight()
{
    bIsActive = false;
    UpdateVisuals(CurrentFluctLight.BaseColor, CurrentFluctLight.EmotionalIntensity * 2.0f);
}

void UFluctLightComponent::UpdateEmotionalState(float NewIntensity)
{
    CurrentFluctLight.EmotionalIntensity = FMath::Clamp(NewIntensity, 0.0f, 1.0f);
    UE_LOG(LogTemp, Log, TEXT("%s's emotional intensity updated to %.2f"), *CurrentFluctLight.Name, CurrentFluctLight.EmotionalIntensity);
    const float TargetIntensity = bIsActive ? CurrentFluctLight.EmotionalIntensity * 4.0f : CurrentFluctLight.EmotionalIntensity * 2.0f;
    UpdateVisuals(bIsActive ? CurrentFluctLight.ActiveColor : CurrentFluctLight.BaseColor, TargetIntensity);
}

void UFluctLightComponent::UpdateVisuals(const FLinearColor& Color, float Intensity)
{
    ApplyColorToParticles(Color);
    ApplyIntensityToLight(Intensity);
}

void UFluctLightComponent::ApplyIntensityToLight(float Intensity)
{
    if (LightAura)
    {
        LightAura->SetIntensity(Intensity);
        LightAura->SetLightColor(bIsActive ? CurrentFluctLight.ActiveColor : CurrentFluctLight.BaseColor);
    }
}

void UFluctLightComponent::ApplyColorToParticles(const FLinearColor& Color)
{
    if (GlowEffect)
    {
        const FVector ColorVector(Color.R, Color.G, Color.B);
        GlowEffect->SetVectorParameter(ParticleColorParameter, ColorVector);
    }
}
