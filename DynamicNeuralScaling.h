#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralScaling.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralScaling : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralScaling();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateNeuralCapacity() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNSP", meta = (ClampMin = "0.0"))
	float InitialNeuralCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNSP")
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNSP", meta = (ClampMin = "0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNSP", meta = (ClampMin = "0.0"))
	float TimeSeconds = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DNSP")
	float NeuralCapacity = 0.0f;
};
