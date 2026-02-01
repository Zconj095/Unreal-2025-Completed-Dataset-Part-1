#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarMemoryRetentionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarMemoryRetentionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarMemoryRetentionComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Memory Retention")
    float InitialCapacity = 100.0f;

    UPROPERTY(EditAnywhere, Category="Memory Retention")
    float DecayRate = 0.1f;

    UPROPERTY(EditAnywhere, Category="Memory Retention")
    float SolarBoost = 50.0f;

    UPROPERTY(EditAnywhere, Category="Memory Retention")
    float Sensitivity = 0.05f;

    UPROPERTY(EditAnywhere, Category="Memory Retention")
    float PeakTime = 5.0f;

    float TimeElapsed = 0.0f;

    float CalculateMemoryRetention(float Time) const;
};
