#include "BioHapticGenreCreationComponent.h"
#include "Engine/World.h"
#include "HapticControllerComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

UBioHapticGenreCreationComponent::UBioHapticGenreCreationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UBioHapticGenreCreationComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!HapticController)
    {
        HapticController = GetOwner() ? GetOwner()->FindComponentByClass<UHapticControllerComponent>() : nullptr;
        if (!HapticController)
        {
            UE_LOG(LogTemp, Warning, TEXT("HapticControllerComponent not found on %s. Attach one or assign it."), *GetNameSafe(GetOwner()));
        }
    }
}

void UBioHapticGenreCreationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float Time = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;

    // Simulate or use externally set heart rate
    if (bSimulateHeartRate)
    {
        HeartRate = GetHeartRateData(Time);
    }

    // Update intensity state
    AdjustGameDynamicsBasedOnHeartRate();

    // Provide haptic feedback
    ProvideHapticFeedback();
}

void UBioHapticGenreCreationComponent::SetHeartRate(float NewHeartRate)
{
    bSimulateHeartRate = false; // switching to external data
    HeartRate = NewHeartRate;
}

// Simulate acquisition of heart rate data (replace with real sensor logic)
float UBioHapticGenreCreationComponent::GetHeartRateData(float TimeSeconds) const
{
    // Unity's Mathf.PingPong(Time.time * 10f, HighHeartRateThreshold * 2)
    const float Length = HighHeartRateThreshold * 2.f;
    const float T = TimeSeconds * FMath::Max(0.f, SimulationSpeed);
    const float Cycle = FMath::Fmod(T, Length * 2.f);
    const float PingPong = Length - FMath::Abs(Cycle - Length);
    return PingPong;
}

void UBioHapticGenreCreationComponent::AdjustGameDynamicsBasedOnHeartRate()
{
    if (HeartRate < LowHeartRateThreshold)
    {
        bGameIntense = false;
        // Adjust gameplay to be more relaxed (hook in gameplay code as needed)
    }
    else if (HeartRate > HighHeartRateThreshold)
    {
        bGameIntense = true;
        // Increase gameplay intensity (hook in gameplay code as needed)
    }
    else
    {
        bGameIntense = false;
        // Maintain normal gameplay dynamics
    }
}

void UBioHapticGenreCreationComponent::ProvideHapticFeedback()
{
    if (!HapticController)
    {
        // Avoid spamming logs every frame; only warn during BeginPlay
        return;
    }

    if (bGameIntense)
    {
        HapticStrength = FMath::GetMappedRangeValueClamped(
            FVector2D(HighHeartRateThreshold, 120.f),
            FVector2D(0.f, 1.f),
            HeartRate);
    }
    else
    {
        HapticStrength = FMath::GetMappedRangeValueClamped(
            FVector2D(LowHeartRateThreshold, HighHeartRateThreshold),
            FVector2D(0.f, 1.f),
            HeartRate);
    }

    HapticController->Vibrate(HapticStrength);
}

