#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HalfMoonActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AHalfMoonActor : public AActor
{
    GENERATED_BODY()

public:
    AHalfMoonActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("Half Moon");
};

