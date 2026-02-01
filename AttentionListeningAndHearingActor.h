// Simple actor that demonstrates the manager usage (Unity Start -> UE BeginPlay)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttentionListeningAndHearingManager.h"
#include "AttentionListeningAndHearingActor.generated.h"

UCLASS()
class PEKBGGAP_API AAttentionListeningAndHearingActor : public AActor
{
    GENERATED_BODY()

public:
    AAttentionListeningAndHearingActor();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UAttentionListeningAndHearingManager* AuditoryManager;
};

