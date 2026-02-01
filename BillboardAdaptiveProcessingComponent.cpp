#include "BillboardAdaptiveProcessingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Components/BillboardComponent.h"

UBillboardAdaptiveProcessingComponent::UBillboardAdaptiveProcessingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UBillboardAdaptiveProcessingComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBillboardAdaptiveProcessingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    ScanWorldIfRequested(DeltaTime);
}

void UBillboardAdaptiveProcessingComponent::NotifyAdded(int32 Count)
{
    NBillboards += FMath::Max(0, Count);
    RecomputeState();
}

void UBillboardAdaptiveProcessingComponent::NotifyRemoved(int32 Count)
{
    NBillboards -= FMath::Max(0, Count);
    NBillboards = FMath::Max<int64>(0, NBillboards);
    RecomputeState();
}

void UBillboardAdaptiveProcessingComponent::RecomputeState()
{
    const int32 NewBoost = FMath::Max(0, (int32)FMath::FloorToFloat((float)NBillboards / (float)FMath::Max(1, ActivationThreshold)) * 10);
    const bool bNewEnable = NBillboards >= ActivationThreshold;
    ApplyState(bNewEnable, NewBoost);
}

void UBillboardAdaptiveProcessingComponent::ScanWorldIfRequested(float DeltaTime)
{
    if (!bPeriodicScan) { return; }
    TimeSinceScan += DeltaTime;
    if (TimeSinceScan < ScanInterval) { return; }
    TimeSinceScan = 0.0f;

    int64 Count = 0;
    if (UWorld* World = GetWorld())
    {
        for (TActorIterator<AActor> It(World); It; ++It)
        {
            TInlineComponentArray<UBillboardComponent*> BillboardComponents(*It);
            Count += BillboardComponents.Num();
        }
    }
    NBillboards = Count;
    RecomputeState();
}

void UBillboardAdaptiveProcessingComponent::ApplyState(bool bEnable, int32 NewBoost)
{
    const bool bChanged = (bEnable != bAdaptiveEnabled) || (NewBoost != BoostPercent);
    bAdaptiveEnabled = bEnable;
    BoostPercent = NewBoost;
    if (bChanged)
    {
        OnAdaptiveStateChanged.Broadcast(bAdaptiveEnabled, BoostPercent);
        UE_LOG(LogTemp, Log, TEXT("Adaptive %s | N=%lld | Boost=%d%%"), bAdaptiveEnabled ? TEXT("ENABLED") : TEXT("DISABLED"), NBillboards, BoostPercent);
    }
}

