// Converted from Unity MonoBehaviour FluctLightBehavior to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "FluctLightComponent.generated.h"

USTRUCT(BlueprintType)
struct FFluctLightDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    FString Name = TEXT("Fluct Light");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float EmotionalIntensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    float MemoryCapacity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    FLinearColor BaseColor = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    FLinearColor ActiveColor = FLinearColor::Red;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UFluctLightComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFluctLightComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    FFluctLightDefinition CurrentFluctLight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    UParticleSystemComponent* GlowEffect = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    UPointLightComponent* LightAura = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light", meta=(ClampMin=0.1f))
    float PulseSpeed = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fluct Light")
    FName ParticleColorParameter = TEXT("Color");

    UFUNCTION(BlueprintCallable, Category="Fluct Light")
    void ActivateLight();

    UFUNCTION(BlueprintCallable, Category="Fluct Light")
    void DeactivateLight();

    UFUNCTION(BlueprintCallable, Category="Fluct Light")
    void UpdateEmotionalState(float NewIntensity);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    bool bIsActive = false;

    void UpdateVisuals(const FLinearColor& Color, float Intensity);
    void SimulatePulsing(float DeltaTime);
    void ApplyIntensityToLight(float Intensity);
    void ApplyColorToParticles(const FLinearColor& Color);
};
