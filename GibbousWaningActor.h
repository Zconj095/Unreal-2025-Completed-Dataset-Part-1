#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GibbousWaningActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AGibbousWaningActor : public AActor
{
    GENERATED_BODY()

public:
    AGibbousWaningActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("Gibbous Waning");
};

