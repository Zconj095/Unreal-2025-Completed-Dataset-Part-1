#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SolarFeedbackLoopComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarFeedbackLoopComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarFeedbackLoopComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Feedback Loop")
    float AdaptationRate = 0.1f;

    UPROPERTY(EditAnywhere, Category="Feedback Loop")
    float ObservedSolarData = 0.0f;

    UPROPERTY(EditAnywhere, Category="Feedback Loop")
    float ExpectedSolarData = 0.0f;

    UPROPERTY(EditAnywhere, Category="Feedback Loop")
    float InitialFeedback = 0.0f;

    UPROPERTY(VisibleInstanceOnly, Category="Feedback Loop")
    float UpdatedFeedback = 0.0f;

    float CalculateFeedback(float Feedback, float Observed, float Expected, float Beta) const;
};
