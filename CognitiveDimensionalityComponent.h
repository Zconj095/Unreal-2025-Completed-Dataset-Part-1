#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveDimensionalityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveDimensionalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveDimensionalityComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Dimensionality")
	float ActiveNeurons = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Dimensionality", meta=(ClampMin="0.1"))
	float TotalNeurons = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Dimensionality")
	float Delta = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Dimensionality")
	float Dimensionality = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Cognitive Dimensionality")
	float CalculateDimensionality() const;
};
