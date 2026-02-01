#pragma once

#include "CoreMinimal.h"

// Blueprint-exposed elemental type enum equivalent to the Unity version
UENUM(BlueprintType)
enum class EElementalTypeTwo : uint8
{
    Fire       UMETA(DisplayName = "Fire"),
    Water      UMETA(DisplayName = "Water"),
    Earth      UMETA(DisplayName = "Earth"),
    Air        UMETA(DisplayName = "Air"),
    Lightning  UMETA(DisplayName = "Lightning"),
    Ice        UMETA(DisplayName = "Ice")
};

