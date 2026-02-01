#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralCapacityScaling.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralCapacityScaling : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralCapacityScaling();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CalculateNeuralCapacity(float InTimeSeconds) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity Scaling", meta = (ClampMin = "0.0"))
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity Scaling")
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capacity Scaling", meta = (ClampMin = "0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity Scaling")
	float TimeSeconds = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capacity Scaling")
	float NeuralCapacity = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Capacity Scaling")
	void SetInitialCapacity(float Value);

	UFUNCTION(BlueprintCallable, Category = "Capacity Scaling")
	void SetGrowthRate(float Value);

	UFUNCTION(BlueprintCallable, Category = "Capacity Scaling")
	void SetMaxCapacity(float Value);

	UFUNCTION(BlueprintCallable, Category = "Capacity Scaling")
	void ResetTime();
};
