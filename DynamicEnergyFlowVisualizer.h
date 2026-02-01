#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicEnergyFlowVisualizer.generated.h"

UCLASS()
class PEKBGGAP_API ADynamicEnergyFlowVisualizer : public AActor
{
	GENERATED_BODY()

public:
	ADynamicEnergyFlowVisualizer();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateEnergyFlow(float TimeSeconds) const;

	UPROPERTY(EditAnywhere, Category = "Visualization", meta = (ClampMin = "0.0"))
	float InitialAmplitude = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Visualization", meta = (ClampMin = "0.0"))
	float DampingCoefficient = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Visualization", meta = (ClampMin = "0.0"))
	float AngularFrequency = 2.0f * PI / 24.0f;

	UPROPERTY(EditAnywhere, Category = "Visualization", meta = (ClampMin = "0.0"))
	float DeltaTime = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Visualization", meta = (ClampMin = "1"))
	int32 Steps = 100;

	UPROPERTY(EditAnywhere, Category = "Visualization")
	TSubclassOf<AActor> PointActorClass;
};
