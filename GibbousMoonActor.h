#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GibbousMoonActor.generated.h"

class UChildActorComponent;
class AGibbousWaxingActor;
class AGibbousWaningActor;

UCLASS(Blueprintable)
class PEKBGGAP_API AGibbousMoonActor : public AActor
{
    GENERATED_BODY()

public:
    AGibbousMoonActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // Child phases (mirrors the two child prefab instances)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* WaxingChild;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* WaningChild;
};

