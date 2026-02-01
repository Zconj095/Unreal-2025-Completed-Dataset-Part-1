// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CircadianRhythmComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCircadianRhythmComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCircadianRhythmComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Circadian Rhythm", meta=(ClampMin="0.0"))
	float Amplitude = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Circadian Rhythm", meta=(ClampMin="0.0"))
	float Frequency = 2.0f * PI / 24.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Circadian Rhythm")
	float Phase = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Circadian Rhythm")
	float RhythmState = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Circadian Rhythm")
	float GetRhythmState() const { return RhythmState; }

private:
	float CalculateRhythm(float TimeSeconds) const;
	float AccumulatedTime = 0.0f;
};
