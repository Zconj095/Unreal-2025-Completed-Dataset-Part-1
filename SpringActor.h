#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ASpringActor : public AActor
{
    GENERATED_BODY()

public:
    ASpringActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    FName SeasonName = TEXT("Spring");
};

