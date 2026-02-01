// Component that simulates Monoflux and Hyperflux ambient signal fields
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FluxSignalGeneratorComponent.generated.h"

UENUM(BlueprintType)
enum class EFluxMode : uint8
{
    Monoflux   UMETA(DisplayName = "Monoflux"),
    Hyperflux  UMETA(DisplayName = "Hyperflux")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFluxSampleEvent, float, Value, const TArray<float>&, Channels);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UFluxSignalGeneratorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFluxSignalGeneratorComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|General")
    EFluxMode Mode = EFluxMode::Monoflux;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|General")
    float SampleRate = 120.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|General")
    bool bNormalizeOutput = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|General")
    bool bUseWorldTime = true;

    UPROPERTY(BlueprintReadOnly, Category = "Flux|Runtime")
    float CurrentValue = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Flux|Runtime")
    TArray<float> CurrentChannels;

    // Monoflux parameters (single coherent channel)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Monoflux")
    float MonoFrequency = 220.0f; // Hz (conceptual)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Monoflux")
    float MonoAmplitude = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Monoflux", meta=(ClampMin=0.0, ClampMax=1.0))
    float MonoEntropy = 0.05f; // small band-limited wobble

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Monoflux")
    float MonoPhase = 0.0f; // radians

    // Hyperflux parameters (multi-channel resonant chaos)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux", meta=(ClampMin=1, ClampMax=64))
    int32 NumChannels = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux")
    TArray<float> ChannelFrequencies; // Hz

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux")
    TArray<float> ChannelAmplitudes; // per-channel amplitude

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux")
    TArray<float> PhaseVelocities; // radians/sec intrinsic drift

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux", meta=(ClampMin=0.0))
    float CouplingStrength = 1.0f; // phase coupling (Kuramoto-like)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux", meta=(ClampMin=0.0))
    float ChaosFactor = 0.3f; // drives turbulent wobble

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Hyperflux")
    bool bRandomizeOnBeginPlay = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Debug")
    bool bDrawDebug = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Debug")
    FColor DebugColor = FColor::Cyan;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Debug")
    float DebugScale = 100.0f;

    UPROPERTY(BlueprintAssignable, Category = "Flux|Events")
    FFluxSampleEvent OnFluxSample;

protected:
    void StepMonoflux(float Time, float Dt);
    void StepHyperflux(float Time, float Dt);
    void EnsureHyperfluxArrays();

private:
    float AccumulatedTime = 0.0f;
    float SampleAccumulator = 0.0f;
    TArray<float> Phases; // per-channel evolving phases
};

