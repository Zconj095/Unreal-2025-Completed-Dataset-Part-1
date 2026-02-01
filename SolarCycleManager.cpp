#include "SolarCycleManager.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASolarCycleManager::ASolarCycleManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASolarCycleManager::BeginPlay()
{
    Super::BeginPlay();
    if (!WaterActor && bAutoFindWaterActor)
    {
        TryAutoFindWater();
    }
}

void ASolarCycleManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Advance day time if requested
    if (bAutoAdvanceDayTime)
    {
        DayTimeHours = FMath::Fmod(DayTimeHours + DayHoursPerSecond * DeltaSeconds, 24.f);
        if (DayTimeHours < 0.f) DayTimeHours += 24.f;
    }

    HandleUpdateSolarCycle(DeltaSeconds);

    // Debug draw sphere indicating solar activity influence
    DrawDebugActivity();
}

void ASolarCycleManager::HandleUpdateSolarCycle(float DeltaSeconds)
{
    // Simulate full solar cycle progression
    if (bSimulateFullCycle && SolarCycleDurationYears > KINDA_SMALL_NUMBER)
    {
        const double SecondsPerYear = 365.0 * 24.0 * 3600.0;
        const double TotalSeconds = (double)SolarCycleDurationYears * SecondsPerYear;
        const double Incr = (double)DeltaSeconds * (double)SimulationSpeed / TotalSeconds;
        CurrentCycleProgress = FMath::Fmod(CurrentCycleProgress + (float)Incr, 1.f);
        if (CurrentCycleProgress < 0.f) CurrentCycleProgress += 1.f;
    }

    // Update tide if day time changed
    const float DayNorm = DayTimeHours / 24.f;
    if (!FMath::IsNearlyEqual(DayNorm, LastDayTimeNormalized))
    {
        LastDayTimeNormalized = DayNorm;
        UpdateSolarTide(DayNorm);
    }

    // Throttle expensive environment updates to ~1 Hz
    EffectsUpdateAccumulator += DeltaSeconds;
    if (EffectsUpdateAccumulator >= 1.f)
    {
        EffectsUpdateAccumulator = 0.f;
        UpdateSolarEffects();
    }
}

void ASolarCycleManager::UpdateSolarTide(float DayTimeNormalized)
{
    const float DailyTideFactor = FMath::Sin(DayTimeNormalized * 2.f * PI) * 0.5f + 0.5f;
    const float CycleInfluence = GetSolarCycleInfluence();

    CurrentSolarTideHeight = BaseSolarTideHeight
        + (DailyTideFactor * SolarTideVariation)
        + (CycleInfluence * SolarMaximumTideBoost);

    UpdateCombinedTideEffects();
}

float ASolarCycleManager::GetSolarCycleInfluence() const
{
    return 1.f - FMath::Abs((CurrentCycleProgress - 0.5f) * 2.f);
}

void ASolarCycleManager::UpdateSolarEffects()
{
    const float CycleInfluence = GetSolarCycleInfluence();
    UpdateAtmosphericEffects(CycleInfluence);
    UpdateAuroraEffects(CycleInfluence);
    UpdateSolarWindEffects(CycleInfluence);
}

void ASolarCycleManager::UpdateAtmosphericEffects(float CycleInfluence)
{
    const float CurrentDensity = BaseAtmosphericDensity * (1.f + CycleInfluence * 0.1f);
    ApplyFogDensity(CurrentDensity);
}

void ASolarCycleManager::UpdateAuroraEffects(float CycleInfluence)
{
    // Example: propagate aurora parameters to child Niagara components if present
    const float CurrentIntensity = AuroraIntensity * CycleInfluence;
    const FLinearColor CurrentColor = FLinearColor::LerpUsingHSV(AuroraBaseColor, FLinearColor(0.8f, 0.2f, 0.2f), CycleInfluence);

    TArray<UNiagaraComponent*> NiagaraComponents;
    GetComponents<UNiagaraComponent>(NiagaraComponents, true);
    for (UNiagaraComponent* NiagaraComp : NiagaraComponents)
    {
        if (!NiagaraComp) continue;
        NiagaraComp->SetVariableFloat(TEXT("AuroraIntensity"), CurrentIntensity);
        NiagaraComp->SetVariableLinearColor(TEXT("AuroraColor"), CurrentColor);
        // Also support User. prefix
        NiagaraComp->SetVariableFloat(TEXT("User.AuroraIntensity"), CurrentIntensity);
        NiagaraComp->SetVariableLinearColor(TEXT("User.AuroraColor"), CurrentColor);
    }
}

void ASolarCycleManager::UpdateSolarWindEffects(float CycleInfluence)
{
    const float CurrentSolarWind = SolarWindStrength * (1.f + CycleInfluence);

    // Cascade
    TArray<UParticleSystemComponent*> ParticleComponents;
    GetComponents<UParticleSystemComponent>(ParticleComponents, true);
    for (UParticleSystemComponent* PSC : ParticleComponents)
    {
        if (!PSC) continue;
        PSC->SetFloatParameter(TEXT("StartSpeed"), CurrentSolarWind);
    }

    // Niagara
    TArray<UNiagaraComponent*> NiagaraComponents;
    GetComponents<UNiagaraComponent>(NiagaraComponents, true);
    for (UNiagaraComponent* NiagaraComp : NiagaraComponents)
    {
        if (!NiagaraComp) continue;
        NiagaraComp->SetVariableFloat(TEXT("StartSpeed"), CurrentSolarWind);
        NiagaraComp->SetVariableFloat(TEXT("User.StartSpeed"), CurrentSolarWind);
    }
}

void ASolarCycleManager::UpdateCombinedTideEffects()
{
    if (!WaterActor)
    {
        return;
    }
    SetActorZ(WaterActor, CurrentSolarTideHeight);
}

void ASolarCycleManager::DrawDebugActivity() const
{
    const float Size = GetSolarCycleInfluence() * 200.f; // scaled for UE units
    DrawDebugSphere(GetWorld(), GetActorLocation(), Size, 16, FColor::Yellow, false, 0.f, 0, 1.5f);
}

void ASolarCycleManager::TryAutoFindWater()
{
    // Try exact name match first
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Actor && Actor->GetName() == TEXT("Water"))
        {
            WaterActor = Actor;
            return;
        }
    }
    // Fallback: find any actor tagged "Water"
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Actor && Actor->ActorHasTag(TEXT("Water")))
        {
            WaterActor = Actor;
            return;
        }
    }
}

void ASolarCycleManager::ApplyFogDensity(float NewDensity)
{
    // Find first ExponentialHeightFog in the world and update its density
    for (TActorIterator<AExponentialHeightFog> It(GetWorld()); It; ++It)
    {
        if (UExponentialHeightFogComponent* FogComp = It->GetComponent())
        {
            FogComp->SetFogDensity(NewDensity);
            return;
        }
    }
}

void ASolarCycleManager::SetActorZ(AActor* Actor, float NewZ) const
{
    if (!Actor) return;
    FVector P = Actor->GetActorLocation();
    P.Z = NewZ;
    Actor->SetActorLocation(P);
}

