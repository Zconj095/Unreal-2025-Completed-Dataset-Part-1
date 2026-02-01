#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralCapacity4.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralCapacity4 : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralCapacity4();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float CalculateDNCB(float TimeSeconds) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB Parameters", meta = (AllowPrivateAccess = "true"))
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB Parameters", meta = (AllowPrivateAccess = "true"))
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DNCB Parameters", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DNCB Parameters", meta = (AllowPrivateAccess = "true"))
	float TimeElapsed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DNCB Parameters", meta = (AllowPrivateAccess = "true"))
	float NeuralCapacity = 0.0f;
};
