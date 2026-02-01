#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveCapacity2Component.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveCapacity2Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveCapacity2Component();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Capacity")
	float Scaling = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Capacity")
	float AtomicDensity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Capacity")
	float NeuralEfficiency = 0.8f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Capacity")
	float CognitiveCapacity = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Cognitive Capacity")
	float CalculateCapacity() const;
};
