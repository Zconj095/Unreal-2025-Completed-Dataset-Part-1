#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinterActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AWinterActor : public AActor
{
    GENERATED_BODY()

public:
    AWinterActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    FName SeasonName = TEXT("Winter");
};

