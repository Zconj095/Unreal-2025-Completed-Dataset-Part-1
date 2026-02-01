#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GibbousWaxingActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AGibbousWaxingActor : public AActor
{
    GENERATED_BODY()

public:
    AGibbousWaxingActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("Gibbous Waxing");
};

