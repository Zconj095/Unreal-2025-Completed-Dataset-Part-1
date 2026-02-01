// Simple trainer to demonstrate creating and practicing OSS skills
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSSSkillComponent.h"
#include "OSSSkillTrainerActor.generated.h"

UCLASS()
class PEKBGGAP_API AOSSSkillTrainerActor : public AActor
{
    GENERATED_BODY()

public:
    AOSSSkillTrainerActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UOSSSkillComponent* OSS;

    // Demo: assign to slot 1
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    int32 DemoHotkeySlot = 1;

    // Demo effects
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    UParticleSystem* DemoParticle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    USoundBase* DemoSound;
};

