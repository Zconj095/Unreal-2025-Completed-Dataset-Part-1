// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChronoMagicalEnergyComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UChronoMagicalEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChronoMagicalEnergyComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float CalculateEnergyFlow(float TimeSeconds) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chrono Energy", meta=(ClampMin="0.0"))
	float InitialAmplitude = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chrono Energy", meta=(ClampMin="0.0"))
	float DampingCoefficient = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chrono Energy", meta=(ClampMin="0.0"))
	float AngularFrequency = 2.0f * PI / 24.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Chrono Energy")
	float EnergyFlow = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Chrono Energy")
	float GetEnergyFlow() const { return EnergyFlow; }
};
