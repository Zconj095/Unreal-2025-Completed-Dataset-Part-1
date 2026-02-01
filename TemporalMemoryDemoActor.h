// Demo actor that exercises UTemporalMemoryComponent with random data and logs recall metrics
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TemporalMemoryComponent.h"
#include "TemporalMemoryDemoActor.generated.h"

UCLASS()
class PEKBGGAP_API ATemporalMemoryDemoActor : public AActor
{
    GENERATED_BODY()

public:
    ATemporalMemoryDemoActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UTemporalMemoryComponent* TM;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    int32 Seed = 1234;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    int32 Dim = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    float AddInterval = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Demo")
    float QueryInterval = 1.0f;

private:
    float TimeSinceAdd = 0.0f;
    float TimeSinceQuery = 0.0f;
};

