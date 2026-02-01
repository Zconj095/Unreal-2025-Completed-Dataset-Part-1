#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutumnActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AAutumnActor : public AActor
{
    GENERATED_BODY()

public:
    AAutumnActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    FName SeasonName = TEXT("Autumn");
};

