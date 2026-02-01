#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialCyclePredictionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialCyclePredictionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialCyclePredictionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Cycle")
	float SemiMajorAxis = 1.496e11f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Cycle")
	float CentralMass = 1.989e30f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Cycle")
	float OrbitalPeriodSeconds = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Cycle")
	float OrbitalPeriodYears = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Celestial Cycle")
	float CalculateOrbitalPeriod(float SemiMajorAxisValue, float CentralMassValue) const;
};
