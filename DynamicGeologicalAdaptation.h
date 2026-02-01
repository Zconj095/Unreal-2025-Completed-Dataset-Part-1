#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicGeologicalAdaptation.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API ADynamicGeologicalAdaptation : public AActor
{
	GENERATED_BODY()

public:
	ADynamicGeologicalAdaptation();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	float UpdateNeuralNetworkSize(float CurrentSize, float Beta, float Capacity, float Delta) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Adaptation", meta = (ClampMin = "0.0"))
	float GrowthRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Adaptation", meta = (ClampMin = "0.0"))
	float MaxCapacity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Adaptation", meta = (ClampMin = "0.0"))
	float InitialNetworkSize = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geological Adaptation", meta = (ClampMin = "0.0"))
	float TimeStep = 0.01f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Geological Adaptation")
	float CurrentNetworkSize = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Geological Adaptation")
	float GetCurrentNetworkSize() const { return CurrentNetworkSize; }
};
