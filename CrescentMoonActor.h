#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrescentMoonActor.generated.h"

class UChildActorComponent;
class ACrescentWaxingActor;
class ACrescentWaningActor;

UCLASS(Blueprintable)
class PEKBGGAP_API ACrescentMoonActor : public AActor
{
    GENERATED_BODY()

public:
    ACrescentMoonActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // Child phases (mirrors the two child prefab instances)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* WaxingChild;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* WaningChild;
};

