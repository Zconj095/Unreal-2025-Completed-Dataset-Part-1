#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMDynamicNeuralCapacityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCMDynamicNeuralCapacityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCMDynamicNeuralCapacityComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Capacity")
	float InitialCapacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Capacity")
	float GrowthRate = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Neural Capacity", meta=(ClampMin="0.01"))
	float MaxCapacity = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Neural Capacity")
	float NeuralCapacity = 1.0f;

	UFUNCTION(BlueprintCallable, Category="Neural Capacity")
	float CalculateCurrentCapacity() const;
};
