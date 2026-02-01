// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialResonanceComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialResonanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialResonanceComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Resonance", meta=(ClampMin="0.0"))
	float Amplitude = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Resonance", meta=(ClampMin="0.01"))
	float Period = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Celestial Resonance")
	float ResonanceFactor = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Celestial Resonance")
	float GetResonanceFactor() const { return ResonanceFactor; }

private:
	float CalculateResonance(float TimeSeconds) const;
};
