#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralCapacity3.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralCapacity3 : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralCapacity3();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CalculateNeuralCapacity(float TimeSeconds) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float InitialNeuralCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true"))
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Neural Capacity", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float MaxNeuralCapacity = 10.0f;
};
