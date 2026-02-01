#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EcologicalResonance.generated.h"

UCLASS()
class PEKBGGAP_API AEcologicalResonance : public AActor
{
	GENERATED_BODY()

public:
	AEcologicalResonance();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void InitializeOscillators();
	void StepSimulation();
	TArray<float> ComputePhaseDerivatives() const;
	void VisualizeResonance();
	float CalculateSynchronization() const;

	UPROPERTY(EditAnywhere, Category = "Kuramoto", meta = (ClampMin = "1"))
	int32 OscillatorCount = 10;

	UPROPERTY(EditAnywhere, Category = "Kuramoto", meta = (ClampMin = "0.0"))
	float CouplingStrength = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Kuramoto")
	float ManaAmplification = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Kuramoto", meta = (ClampMin = "0.001"))
	float TimeStep = 0.01f;

	UPROPERTY(EditAnywhere, Category = "Kuramoto", meta = (ClampMin = "0.01"))
	float SimulationDuration = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Kuramoto")
	bool bDrawDebugGraph = true;

	UPROPERTY(EditAnywhere, Category = "Kuramoto", meta = (ClampMin = "1.0"))
	float GraphSpacing = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Kuramoto")
	bool bLogSynchronization = true;

	TArray<float> Phases;
	TArray<float> NaturalFrequencies;
	TArray<TArray<float>> PhaseHistory;

	float TimeAccumulator = 0.0f;
	float ElapsedTime = 0.0f;
	bool bSimulationComplete = false;
	bool bGraphDrawn = false;
};
