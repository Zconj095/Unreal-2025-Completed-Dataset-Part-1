#include "HapticControllerComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UHapticControllerComponent::UHapticControllerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHapticControllerComponent::Vibrate(float Strength)
{
    const float Clamped = FMath::Clamp(Strength, 0.f, 1.f);
    if (Clamped <= 0.f)
    {
        return;
    }

    APlayerController* PC = nullptr;

    if (APawn* AsPawn = Cast<APawn>(GetOwner()))
    {
        PC = Cast<APlayerController>(AsPawn->GetController());
    }

    if (!PC)
    {
        PC = UGameplayStatics::GetPlayerController(this, FallbackPlayerIndex);
    }

    if (PC)
    {
        // Trigger gamepad rumble on all motors for a short pulse
        PC->PlayDynamicForceFeedback(Clamped, PulseDuration, true, true, true, true);
    }
}

