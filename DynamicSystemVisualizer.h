#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicSystemVisualizer.generated.h"

class UStaticMeshComponent;

UCLASS()
class PEKBGGAP_API ADynamicSystemVisualizer : public AActor
{
	GENERATED_BODY()

public:
	ADynamicSystemVisualizer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateDisplacements();

	UPROPERTY(EditAnywhere, Category = "Dynamics", meta = (ClampMin = "0.0"))
	float DampingRatio = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Dynamics", meta = (ClampMin = "0.0"))
	float NaturalFrequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Dynamics", meta = (ClampMin = "0.0"))
	float SimulationTime = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Dynamics", meta = (ClampMin = "1"))
	int32 Steps = 1000;

	UPROPERTY(EditAnywhere, Category = "Dynamics", meta = (ClampMin = "0.0"))
	float ForceFrequency = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Dynamics")
	UStaticMeshComponent* VisualMesh;

	TArray<float> Displacements;
	int32 CurrentIndex = 0;
	float StepInterval = 0.1f;
	float TimeAccumulator = 0.0f;
};
