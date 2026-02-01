#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BioHapticGenreCreationComponent.generated.h"

class UHapticControllerComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBioHapticGenreCreationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBioHapticGenreCreationComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Thresholds for heart rate that drive game intensity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BioHaptics|Thresholds")
    float LowHeartRateThreshold = 60.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BioHaptics|Thresholds")
    float HighHeartRateThreshold = 100.f;

    // Simulated heart rate configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BioHaptics|Simulation")
    bool bSimulateHeartRate = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BioHaptics|Simulation", meta=(EditCondition="bSimulateHeartRate", ClampMin="0.0"))
    float SimulationSpeed = 10.f; // similar to Time.time * 10f in Unity

    // Reference to the haptic controller component
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BioHaptics")
    UHapticControllerComponent* HapticController = nullptr;

    // Runtime state
    UPROPERTY(BlueprintReadOnly, Category="BioHaptics|Runtime")
    float HeartRate = 70.f;

    UPROPERTY(BlueprintReadOnly, Category="BioHaptics|Runtime")
    bool bGameIntense = false;

    UPROPERTY(BlueprintReadOnly, Category="BioHaptics|Runtime")
    float HapticStrength = 0.f;

    UFUNCTION(BlueprintCallable, Category="BioHaptics")
    void SetHeartRate(float NewHeartRate);

    UFUNCTION(BlueprintPure, Category="BioHaptics")
    float GetHeartRate() const { return HeartRate; }

protected:
    float GetHeartRateData(float TimeSeconds) const;
    void AdjustGameDynamicsBasedOnHeartRate();
    void ProvideHapticFeedback();
};

