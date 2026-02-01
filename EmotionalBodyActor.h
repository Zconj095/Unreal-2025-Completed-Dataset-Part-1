#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmotionalBodyActor.generated.h"

class USceneComponent;
class UNiagaraComponent;
class UParticleSystemComponent;

UCLASS(Blueprintable)
class PEKBGGAP_API AEmotionalBodyActor : public AActor
{
    GENERATED_BODY()

public:
    AEmotionalBodyActor();

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // FX layer to configure (Niagara or Cascade)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura")
    USceneComponent* AuraLayer = nullptr;

    // Defaults mirror Unity YAML
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Params")
    FLinearColor AuraColor = FLinearColor(1.f, 0.7f, 0.7f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Params")
    float AuraTransparency = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Params")
    float ParticleSize = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Params")
    int32 ParticleCount = 2000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Params")
    float AuraRadius = 2.f;

    // Parameter names expected by the FX system
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Param Names")
    FName AuraColorParam = TEXT("AuraColor");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Param Names")
    FName AuraTransparencyParam = TEXT("AuraTransparency");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Param Names")
    FName ParticleSizeParam = TEXT("ParticleSize");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Param Names")
    FName ParticleCountParam = TEXT("ParticleCount");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aura|Param Names")
    FName AuraRadiusParam = TEXT("AuraRadius");

    UFUNCTION(BlueprintCallable, Category="Aura")
    void ApplyAuraSettings();

private:
    void ApplyToNiagara(UNiagaraComponent* NiagaraComp) const;
    void ApplyToCascade(UParticleSystemComponent* ParticleComp) const;
};

