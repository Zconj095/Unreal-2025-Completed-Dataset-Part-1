#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrescentWaxingActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ACrescentWaxingActor : public AActor
{
    GENERATED_BODY()

public:
    ACrescentWaxingActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // Display name (Unity prefab labeled "Cresent Waxing"), corrected here
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("Crescent Waxing");
};

