#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeasonTypes.h"
#include "SeasonEnergeticManager.generated.h"

class USceneComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

USTRUCT(BlueprintType)
struct PEKBGGAP_API FSeasonParticleParams
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    float SimulationSpeed = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    float StartSize = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    float StartLifetime = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    float EmissionRate = 20.f;
};

UCLASS(Blueprintable)
class PEKBGGAP_API ASeasonEnergeticManager : public AActor
{
    GENERATED_BODY()

public:
    ASeasonEnergeticManager();

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    ESeason Season = ESeason::Spring;

    // Roots to scan for particle systems (children Niagara or Cascade)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Targets")
    USceneComponent* ChakraRoot = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Targets")
    USceneComponent* AuraRoot = nullptr;

    // Parameter names expected by particle systems
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Params|Names")
    FName SimulationSpeedParam = TEXT("SimulationSpeed");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Params|Names")
    FName StartSizeParam = TEXT("StartSize");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Params|Names")
    FName StartLifetimeParam = TEXT("StartLifetime");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Params|Names")
    FName EmissionRateParam = TEXT("RateOverTime");

    // Chakra seasonal presets
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Presets")
    FSeasonParticleParams ChakraSpring { 1.2f, 1.1f, 5.0f, 30.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Presets")
    FSeasonParticleParams ChakraSummer { 1.5f, 1.3f, 4.5f, 40.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Presets")
    FSeasonParticleParams ChakraAutumn { 1.0f, 1.0f, 6.0f, 25.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Presets")
    FSeasonParticleParams ChakraWinter { 0.7f, 1.2f, 7.0f, 20.f };

    // Aura seasonal presets
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Presets")
    FSeasonParticleParams AuraSpring { 1.3f, 1.2f, 5.0f, 35.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Presets")
    FSeasonParticleParams AuraSummer { 1.7f, 1.5f, 4.0f, 50.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Presets")
    FSeasonParticleParams AuraAutumn { 1.0f, 1.0f, 6.5f, 30.f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Presets")
    FSeasonParticleParams AuraWinter { 0.6f, 1.2f, 7.5f, 15.f };

    UFUNCTION(BlueprintCallable, Category="Season")
    void ApplyChakraParticleBehavior();

    UFUNCTION(BlueprintCallable, Category="Season")
    void ApplyAuraParticleBehavior();

private:
    FSeasonParticleParams GetChakraParamsForSeason(ESeason InSeason) const;
    FSeasonParticleParams GetAuraParamsForSeason(ESeason InSeason) const;
    void ApplyParamsToRoot(USceneComponent* Root, const FSeasonParticleParams& Params) const;
    void ApplyToNiagara(UNiagaraComponent* NiagaraComp, const FSeasonParticleParams& Params) const;
    void ApplyToCascade(UParticleSystemComponent* ParticleComp, const FSeasonParticleParams& Params) const;
};

