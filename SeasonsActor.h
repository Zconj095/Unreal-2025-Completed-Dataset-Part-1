#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeasonsActor.generated.h"

class UChildActorComponent;
class ASpringActor;
class ASummerActor;
class AAutumnActor;
class AWinterActor;

UCLASS(Blueprintable)
class PEKBGGAP_API ASeasonsActor : public AActor
{
    GENERATED_BODY()

public:
    ASeasonsActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* Spring;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* Summer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* Autumn;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UChildActorComponent* Winter;
};

