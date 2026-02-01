#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BioevolutionaryCognitiveLoadComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBioevolutionaryCognitiveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBioevolutionaryCognitiveLoadComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive Load")
	float TimeConstant = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive Load")
	float EnvironmentalStimuli = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive Load")
	float GeneticStimuli = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive Load")
	float StartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive Load")
	float EndTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive Load", meta = (ClampMin = "1"))
	int32 IntegrationSteps = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cognitive Load")
	float CognitiveLoad = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Cognitive Load")
	float CalculateCognitiveLoad(float Environmental, float Genetic, float Tau, float Start, float End, int32 Steps) const;

	UFUNCTION(BlueprintCallable, Category = "Cognitive Load")
	float StimuliFunction(float Environmental, float Genetic, float TimeSeconds) const;
};
