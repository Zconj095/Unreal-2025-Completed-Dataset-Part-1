// Adaptive processing for billboard textures with thresholding and boost computation
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BillboardAdaptiveProcessingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAdaptiveStateChanged, bool, bEnabled, int32, BoostPercent);

UCLASS(ClassGroup=(Rendering), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBillboardAdaptiveProcessingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBillboardAdaptiveProcessingComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Threshold N_billboards to enable adaptive mode
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Adaptive|Threshold")
    int32 ActivationThreshold = 100000;

    // Optional periodic world scan for UBillboardComponent count
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Adaptive|Threshold")
    bool bPeriodicScan = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Adaptive|Threshold", meta=(EditCondition="bPeriodicScan", ClampMin="0.01", ClampMax="10.0"))
    float ScanInterval = 1.0f;

    // Current totals
    UPROPERTY(BlueprintReadOnly, Category="Adaptive|Runtime")
    int64 NBillboards = 0;

    UPROPERTY(BlueprintReadOnly, Category="Adaptive|Runtime")
    int32 BoostPercent = 0; // P_boost = floor(N/100000)*10

    UPROPERTY(BlueprintReadOnly, Category="Adaptive|Runtime")
    bool bAdaptiveEnabled = false;

    // Notify system when textures were added/removed externally
    UFUNCTION(BlueprintCallable, Category="Adaptive|Threshold")
    void NotifyAdded(int32 Count = 1);

    UFUNCTION(BlueprintCallable, Category="Adaptive|Threshold")
    void NotifyRemoved(int32 Count = 1);

    // Force recompute based on current NBillboards
    UFUNCTION(BlueprintCallable, Category="Adaptive|Threshold")
    void RecomputeState();

    // Event fired when adaptive state toggles or boost changes
    UPROPERTY(BlueprintAssignable, Category="Adaptive|Events")
    FOnAdaptiveStateChanged OnAdaptiveStateChanged;

private:
    void ScanWorldIfRequested(float DeltaTime);
    void ApplyState(bool bEnable, int32 NewBoost);

    float TimeSinceScan = 0.0f;
};

