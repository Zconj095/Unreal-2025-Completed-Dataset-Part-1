#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraArtificialEnergyComponent.generated.h"

class USceneComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAuraArtificialEnergyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAuraArtificialEnergyComponent();

    virtual void BeginPlay() override;

    // Layers (can be Niagara or Cascade components assigned from the actor)
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

    // Target parameter values (Unity parity)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float SimulationSpeed = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float StartSize = 0.6f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float StartLifetime = 4.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura Params")
    float RateOverTime = 40.0f;

    // Parameter names expected by the particle systems (must be exposed as user parameters in Niagara
    // or parameter distributions in Cascade)
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
    void ApplyArtificialEnergyToAura(USceneComponent* AuraLayer);

private:
    void ApplyToNiagara(class UNiagaraComponent* NiagaraComp) const;
    void ApplyToCascade(class UParticleSystemComponent* ParticleComp) const;
    TArray<USceneComponent*> GetAllLayers() const;
};

