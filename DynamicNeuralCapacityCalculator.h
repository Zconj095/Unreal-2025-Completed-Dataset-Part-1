#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralCapacityCalculator.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralCapacityCalculator : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralCapacityCalculator();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CalculateNeuralCapacity(float TimeSeconds) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true"))
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Settings", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float SimulationTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Settings", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float TimeStep = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true"))
	float CurrentTime = 0.0f;
};
