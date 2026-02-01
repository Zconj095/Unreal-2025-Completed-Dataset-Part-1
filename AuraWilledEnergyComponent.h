#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraWilledEnergyComponent.generated.h"

class USceneComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAuraWilledEnergyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAuraWilledEnergyComponent();

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

    // Defaults for willed energy
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float SimulationSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float StartSize = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float StartLifetime = 6.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float RateOverTime = 15.0f;

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
    void ApplyWilledEnergyToAura(USceneComponent* AuraLayer);

private:
    TArray<USceneComponent*> GetAllLayers() const;
    void ApplyToNiagara(class UNiagaraComponent* NiagaraComp) const;
    void ApplyToCascade(class UParticleSystemComponent* ParticleComp) const;
};

