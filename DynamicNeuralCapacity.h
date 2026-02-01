#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralCapacity.generated.h"

UCLASS()
class PEKBGGAP_API ADynamicNeuralCapacity : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralCapacity();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CalculateNeuralCapacity(float TimeSeconds) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float MaxCapacity = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float TimeStepFactor = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true"))
	float CurrentTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true"))
	float NeuralCapacity = 0.0f;
};
