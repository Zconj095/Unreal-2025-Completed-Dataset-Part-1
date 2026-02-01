#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElvenNeuralMagicalConnectivity.generated.h"

class USplineComponent;

UCLASS()
class PEKBGGAP_API AElvenNeuralMagicalConnectivity : public AActor
{
	GENERATED_BODY()

public:
	AElvenNeuralMagicalConnectivity();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SimulateSignal();
	float CalculateSignalIntensity(float TimeSeconds) const;
	void SpawnDebugPoints() const;

	UPROPERTY(EditAnywhere, Category = "Signal")
	float ManaAmplificationFactor = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Signal")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Signal")
	float AmplitudeA = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Signal")
	float AmplitudeB = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Signal", meta = (ClampMin = "0.01"))
	float SimulationTime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Signal", meta = (ClampMin = "0.01"))
	float TimeStep = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Visualization")
	float LineWidth = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Visualization")
	FColor LineColor = FColor::Blue;

	UPROPERTY(VisibleAnywhere, Category = "Visualization")
	USplineComponent* SignalSpline = nullptr;

	TArray<FVector> SimulationPoints;
	float ElapsedTime = 0.0f;
};
