#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoonPhasesActor.generated.h"

class UChildActorComponent;
class ANewMoonActor;
class AFullMoonActor;
class AHalfMoonActor;
class AGibbousMoonActor;
class ACrescentMoonActor;

UCLASS(Blueprintable)
class PEKBGGAP_API AMoonPhasesActor : public AActor
{
    GENERATED_BODY()

public:
    AMoonPhasesActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // Children corresponding to Unity prefab instances
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* NewMoon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* FullMoon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* HalfMoon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* GibbousMoon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* CrescentMoon;
};

