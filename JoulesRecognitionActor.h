// Demo actor for JoulesRecognitionManager
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoulesRecognitionManager.h"
#include "JoulesRecognitionActor.generated.h"

UCLASS()
class PEKBGGAP_API AJoulesRecognitionActor : public AActor
{
    GENERATED_BODY()

public:
    AJoulesRecognitionActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UJoulesRecognitionManager* Manager;
};

