// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveCapacityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveCapacityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveCapacityComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognition")
	float Proportionality = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognition")
	float EventDensity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognition")
	float Adaptability = 0.8f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognition")
	float CognitiveCapacity = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Cognition")
	float CalculateCognitiveCapacity() const;
};
