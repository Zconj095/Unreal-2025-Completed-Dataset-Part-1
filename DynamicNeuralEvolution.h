#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicNeuralEvolution.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicNeuralEvolution : public AActor
{
	GENERATED_BODY()

public:
	ADynamicNeuralEvolution();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolution Parameters", meta = (ClampMin = "0.0"))
	float InitialNeuralSize = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolution Parameters")
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolution Parameters", meta = (ClampMin = "0.01"))
	float CarryingCapacity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Settings", meta = (ClampMin = "0.0"))
	float TimeStep = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simulation Settings", meta = (ClampMin = "0.0"))
	float TotalTime = 20.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation Settings", meta = (AllowPrivateAccess = "true"))
	float ElapsedTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation Settings", meta = (AllowPrivateAccess = "true"))
	float CurrentNeuralSize = 0.0f;

private:
	float SimulateEvolution(float CurrentSize, float Beta, float Capacity, float Delta) const;
};
