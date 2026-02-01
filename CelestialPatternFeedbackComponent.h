// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialPatternFeedbackComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialPatternFeedbackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialPatternFeedbackComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void LogFeedback() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Feedback", meta=(ClampMin="0.0"))
	float Beta = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Feedback")
	float ObservedPatterns = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Feedback")
	float ExpectedPatterns = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Feedback")
	float FeedbackState = 0.0f;
};
