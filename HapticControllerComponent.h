#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HapticControllerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UHapticControllerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHapticControllerComponent();

    // Vibrate with normalized strength [0..1]
    UFUNCTION(BlueprintCallable, Category="Haptics")
    void Vibrate(float Strength);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Haptics")
    float PulseDuration = 0.1f; // seconds

    // If owner is not a Pawn with a PlayerController, fallback player index
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Haptics")
    int32 FallbackPlayerIndex = 0;
};

