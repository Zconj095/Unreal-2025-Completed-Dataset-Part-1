#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveEvolutionaryPotentialComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveEvolutionaryPotentialComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveEvolutionaryPotentialComponent();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateCEP() const;
	float WaveFunction(float X, float TimeSeconds) const;
	float ConjugateWaveFunction(float X, float TimeSeconds) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evolutionary Potential")
	float XMin = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evolutionary Potential")
	float XMax = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evolutionary Potential", meta=(ClampMin="1"))
	int32 NumSteps = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evolutionary Potential")
	float StartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Evolutionary Potential")
	float EndTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evolutionary Potential")
	float CEPValue = 0.0f;
};
