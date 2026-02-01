// Demo actor to host FluxSignalGeneratorComponent
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FluxSignalGeneratorComponent.h"
#include "FluxSignalActor.generated.h"

UCLASS()
class PEKBGGAP_API AFluxSignalActor : public AActor
{
    GENERATED_BODY()

public:
    AFluxSignalActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Flux")
    UFluxSignalGeneratorComponent* FluxComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flux|Debug")
    bool bLogSamples = true;

private:
    UFUNCTION()
    void OnFluxSample(float Value, const TArray<float>& Channels);
};

