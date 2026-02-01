#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChakraWilledEnergyComponent.generated.h"

class USceneComponent;
class UParticleSystemComponent;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UChakraWilledEnergyComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UChakraWilledEnergyComponent();

    virtual void BeginPlay() override;

    // Chakra layer components (assign Niagara or Cascade components)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* RootChakra = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* SacralChakra = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* SolarPlexusChakra = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* HeartChakra = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* ThroatChakra = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* ThirdEyeChakra = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Layers")
    USceneComponent* CrownChakra = nullptr;

    // Defaults for willed energy
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params")
    float SimulationSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params")
    float StartSize = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params")
    float StartLifetime = 6.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params")
    float RateOverTime = 15.0f;

    // Parameter names in particle systems
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params|Names")
    FName SimulationSpeedParam = TEXT("SimulationSpeed");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params|Names")
    FName StartSizeParam = TEXT("StartSize");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params|Names")
    FName StartLifetimeParam = TEXT("StartLifetime");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chakra Params|Names")
    FName RateOverTimeParam = TEXT("RateOverTime");

    UFUNCTION(BlueprintCallable, Category="Chakra")
    void ApplyWilledEnergyToChakras();

    UFUNCTION(BlueprintCallable, Category="Chakra")
    void ApplyWilledEnergyToChakra(USceneComponent* ChakraLayer);

private:
    TArray<USceneComponent*> GetAllChakras() const;
    void ApplyToNiagara(class UNiagaraComponent* NiagaraComp) const;
    void ApplyToCascade(class UParticleSystemComponent* ParticleComp) const;
};

