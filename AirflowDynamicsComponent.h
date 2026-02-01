#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirflowDynamicsComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAirflowDynamicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAirflowDynamicsComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Atmospheric static pressure (P). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Airflow Dynamics")
	float StaticPressure = 101325.0f;

	/** Air density (ρ). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Airflow Dynamics")
	float AirDensity = 1.225f;

	/** Airflow velocity (v). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Airflow Dynamics")
	float AirflowVelocity = 10.0f;

	/** Gravitational acceleration (g). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Airflow Dynamics")
	float GravitationalAccel = 9.81f;

	/** Height (h). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Airflow Dynamics")
	float Height = 5.0f;

	/** Magical energy flux (μΦ). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Airflow Dynamics")
	float MagicalEnergyFlux = 100.0f;

	/** Computed constant result from Bernoulli's equation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Airflow Dynamics")
	float CalculatedConstant = 0.0f;

	/** Calculates Bernoulli constant: P + 0.5ρv^2 + ρgh + μΦ. */
	UFUNCTION(BlueprintCallable, Category = "Airflow Dynamics")
	float CalculateBernoulliConstant(float Pressure, float Density, float Velocity, float Gravity, float HeightValue, float EnergyFlux) const;

	/** Logs a mock neural network prediction for the constant. */
	UFUNCTION(BlueprintCallable, Category = "Airflow Dynamics")
	void LogNeuralNetworkPrediction() const;

	/** Logs a mock TensorFlow computation for the constant. */
	UFUNCTION(BlueprintCallable, Category = "Airflow Dynamics")
	void LogTensorFlowComputation() const;
};
