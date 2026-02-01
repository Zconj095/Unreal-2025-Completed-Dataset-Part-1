#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SummerActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ASummerActor : public AActor
{
    GENERATED_BODY()

public:
    ASummerActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Season")
    FName SeasonName = TEXT("Summer");
};

