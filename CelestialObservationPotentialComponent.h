// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "CelestialObservationPotentialComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialObservationPotentialComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialObservationPotentialComponent();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateObservationPotential() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observation")
	FRuntimeFloatCurve WaveFunctionCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observation")
	FRuntimeFloatCurve HamiltonianCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observation", meta = (ClampMin = "0.0"))
	float IntegrationStart = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observation", meta = (ClampMin = "0.0"))
	float IntegrationEnd = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Observation", meta = (ClampMin = "1"))
	int32 IntegrationSteps = 100;
};
