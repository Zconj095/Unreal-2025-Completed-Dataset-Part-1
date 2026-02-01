#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "CognitiveEntanglementComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveEntanglementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCognitiveEntanglementComponent();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateCEP() const;
	float WaveFunction(float X, float TimeSeconds) const;
	float ConjugateWaveFunction(float X, float TimeSeconds) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Entanglement")
	float XMin = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Entanglement")
	float XMax = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Entanglement", meta=(ClampMin="1"))
	int32 NumSteps = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Entanglement")
	float StartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Entanglement")
	float EndTime = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Entanglement")
	float CEPValue = 0.0f;
};
