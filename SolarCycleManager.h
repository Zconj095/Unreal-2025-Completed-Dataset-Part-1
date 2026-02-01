#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarCycleManager.generated.h"

class UExponentialHeightFogComponent;
class UNiagaraComponent;
class UParticleSystemComponent;

UCLASS(Blueprintable)
class PEKBGGAP_API ASolarCycleManager : public AActor
{
    GENERATED_BODY()

public:
    ASolarCycleManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // Solar Cycle Settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Cycle")
    float SolarCycleDurationYears = 11.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Cycle", meta=(ClampMin=0.0, ClampMax=1.0))
    float CurrentCycleProgress = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Cycle")
    bool bSimulateFullCycle = false;

    // Scales how quickly the 11-year cycle advances (1 = real-time ratio against DurationYears)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Cycle")
    float SimulationSpeed = 1.f;

    // Daytime simulation (hours in [0,24)). Set bAutoAdvanceDayTime=false to drive externally.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Of Day")
    bool bAutoAdvanceDayTime = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Of Day", meta=(ClampMin=0.0, ClampMax=24.0))
    float DayTimeHours = 12.f;

    // How many in-game hours pass per real second when auto advancing
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time Of Day")
    float DayHoursPerSecond = 0.1f;

    // Solar Tide Settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Tide")
    float BaseSolarTideHeight = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Tide")
    float SolarTideVariation = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Solar Tide")
    float SolarMaximumTideBoost = 0.2f;

    // Environmental Effects
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Environment")
    float BaseAtmosphericDensity = 0.02f; // closer to UE fog defaults

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Environment")
    float SolarWindStrength = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Environment")
    float AuroraIntensity = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Environment")
    FLinearColor AuroraBaseColor = FLinearColor(0.1f, 0.8f, 0.3f);

    // Optional water actor to apply tide height to (Z position)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Environment")
    AActor* WaterActor = nullptr;

    // If true and WaterActor is null, tries to find an actor named "Water" at BeginPlay
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Environment")
    bool bAutoFindWaterActor = true;

    UFUNCTION(BlueprintPure, Category="Solar Cycle")
    float GetCurrentSolarCycleProgress() const { return CurrentCycleProgress; }

    UFUNCTION(BlueprintPure, Category="Solar Cycle")
    bool IsSolarMaximum() const { return FMath::Abs(CurrentCycleProgress - 0.5f) < 0.1f; }

    UFUNCTION(BlueprintPure, Category="Solar Cycle")
    bool IsSolarMinimum() const { return (CurrentCycleProgress < 0.1f) || (CurrentCycleProgress > 0.9f); }

protected:
    void HandleUpdateSolarCycle(float DeltaSeconds);
    void UpdateSolarTide(float DayTimeNormalized);
    float GetSolarCycleInfluence() const;
    void UpdateSolarEffects();
    void UpdateAtmosphericEffects(float CycleInfluence);
    void UpdateAuroraEffects(float CycleInfluence);
    void UpdateSolarWindEffects(float CycleInfluence);
    void UpdateCombinedTideEffects();
    void DrawDebugActivity() const;
    void TryAutoFindWater();
    void ApplyFogDensity(float NewDensity);
    void SetActorZ(AActor* Actor, float NewZ) const;

private:
    float CurrentSolarTideHeight = 0.f;
    float LastDayTimeNormalized = -1.f;
    float EffectsUpdateAccumulator = 0.f;
};

