#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveEvolutionaryExpansionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PEKBGGAP_API UCognitiveEvolutionaryExpansionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveEvolutionaryExpansionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float Alpha = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution", meta=(ClampMin="0.1"))
	float TotalNeurons = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float Dimensionality = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float ConnectivityDensity = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Evolution")
	float CEEValue = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Cognitive Evolution")
	float CalculateCEE() const;
};
