#pragma once

#include "CoreMinimal.h"
#include "SeasonTypes.generated.h"

UENUM(BlueprintType)
enum class ESeason : uint8
{
    Spring UMETA(DisplayName="Spring"),
    Summer UMETA(DisplayName="Summer"),
    Autumn UMETA(DisplayName="Autumn"),
    Winter UMETA(DisplayName="Winter")
};

