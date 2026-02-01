#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NewMoonActor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ANewMoonActor : public AActor
{
    GENERATED_BODY()

public:
    ANewMoonActor();

    // Root transform equivalent to Unity's Transform on the prefab
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    USceneComponent* Root;

    // Name shown/used for identification (mirrors prefab name "New Moon")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moon")
    FName MoonName = TEXT("New Moon");
};

