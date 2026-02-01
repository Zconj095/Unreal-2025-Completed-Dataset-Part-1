#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialEnergyIntegrationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialEnergyIntegrationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialEnergyIntegrationComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** ΔE_a: Energy flux multiplier. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Energy")
	float EnergyFlux = 1.0f;

	/** Φ_a(t): Energy distribution curve. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Energy")
	FInterpCurveFloat EnergyDistribution;

	/** Integrated energy (E_a). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Energy")
	float IntegratedEnergy = 0.0f;

private:
	float PreviousTime = 0.0f;
};
