// Actor demo for AttentionSpanManager (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttentionSpanManager.h"
#include "AttentionSpanActor.generated.h"

UCLASS()
class PEKBGGAP_API AAttentionSpanActor : public AActor
{
    GENERATED_BODY()

public:
    AAttentionSpanActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UAttentionSpanManager* AttentionManager;
};

