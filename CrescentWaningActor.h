#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrescentWaningActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ACrescentWaningActor : public AActor
{
    GENERATED_BODY()

public:
    ACrescentWaningActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // Display name (Unity prefab labeled "Cresent Wanning"), corrected here
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("Crescent Waning");
};

