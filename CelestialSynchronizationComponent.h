// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialSynchronizationComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialSynchronizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialSynchronizationComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Synchronization", meta=(ClampMin="0.01"))
	float BaselineActivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Synchronization")
	float Amplitude = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Synchronization")
	float AngularFrequency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Celestial Synchronization")
	float PhaseOffset = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Celestial Synchronization")
	float NeuralActivity = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Celestial Synchronization")
	float GetNeuralActivity() const { return NeuralActivity; }

private:
	float CalculateNeuralActivity(float TimeSeconds) const;
	float AccumulatedTime = 0.0f;
};
