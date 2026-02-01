#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FullMoonActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AFullMoonActor : public AActor
{
    GENERATED_BODY()

public:
    AFullMoonActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("Full Moon");
};

