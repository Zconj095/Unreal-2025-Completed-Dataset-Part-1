#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralCapacityBiosynthesis.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralCapacityBiosynthesis : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralCapacityBiosynthesis();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateNeuralCapacity(float TimeSeconds) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB", meta = (AllowPrivateAccess = "true"))
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB", meta = (AllowPrivateAccess = "true"))
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB", meta = (AllowPrivateAccess = "true"))
	float Time = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DNCB", meta = (AllowPrivateAccess = "true"))
	float NeuralCapacity = 0.0f;
};
