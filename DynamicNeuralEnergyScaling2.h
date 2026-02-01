#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralEnergyScaling2.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralEnergyScaling2 : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralEnergyScaling2();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateNeuralCapacity() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNES", meta = (ClampMin = "0.0"))
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNES")
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNES", meta = (ClampMin = "0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNES", meta = (ClampMin = "0.0"))
	float TimeSeconds = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DNES")
	float NeuralCapacity = 0.0f;
};
