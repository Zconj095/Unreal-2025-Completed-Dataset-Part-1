#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralEnergyScaling.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralEnergyScaling : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralEnergyScaling();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CalculateNeuralEnergyCapacity(float Elapsed) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Scaling", meta = (ClampMin = "0.0"))
	float InitialEnergyCapacity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Scaling")
	float GrowthRate = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Scaling", meta = (ClampMin = "0.01"))
	float MaxCapacity = 200.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Scaling")
	float ElapsedTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Scaling")
	float NeuralEnergyCapacity = 0.0f;
};
