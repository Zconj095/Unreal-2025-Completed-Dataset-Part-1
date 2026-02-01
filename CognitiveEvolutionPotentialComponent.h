#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveEvolutionPotentialComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveEvolutionPotentialComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveEvolutionPotentialComponent();

protected:
	virtual void BeginPlay() override;

private:
	float IntegrateCEP() const;

	float WaveFunction(float X, float TimeSeconds) const;
	float ConjugateWaveFunction(float X, float TimeSeconds) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float XMin = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float XMax = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution", meta=(ClampMin="1"))
	int32 NumSteps = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float StartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Evolution")
	float EndTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Evolution")
	float CEPValue = 0.0f;
};
