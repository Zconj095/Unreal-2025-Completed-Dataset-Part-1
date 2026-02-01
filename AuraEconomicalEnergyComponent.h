#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraEconomicalEnergyComponent.generated.h"

class USceneComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAuraEconomicalEnergyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAuraEconomicalEnergyComponent();

    virtual void BeginPlay() override;

    // Layers (assign Niagara or Cascade components)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* EthericBody = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* EmotionalBody = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* MentalBody = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* AstralBody = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* EthericTemplate = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* CelestialBody = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Layers")
    USceneComponent* CausalBody = nullptr;

    // Defaults for economical energy (slow, small, long-lived, sparse)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float SimulationSpeed = 0.7f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float StartSize = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float StartLifetime = 9.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float RateOverTime = 8.0f;

    // Parameter names
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params|Names")
    FName SimulationSpeedParam = TEXT("SimulationSpeed");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params|Names")
    FName StartSizeParam = TEXT("StartSize");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params|Names")
    FName StartLifetimeParam = TEXT("StartLifetime");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params|Names")
    FName RateOverTimeParam = TEXT("RateOverTime");

    UFUNCTION(BlueprintCallable, Category="Aura")
    void ApplyContentAura();

    UFUNCTION(BlueprintCallable, Category="Aura")
    void ApplyEconomicalEnergyToAura(USceneComponent* AuraLayer);

private:
    TArray<USceneComponent*> GetAllLayers() const;
    void ApplyToNiagara(class UNiagaraComponent* NiagaraComp) const;
    void ApplyToCascade(class UParticleSystemComponent* ParticleComp) const;
};

