#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AlignmentScoringTrainerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAlignmentScoringTrainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAlignmentScoringTrainerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Number of inputs for the mock trainer. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alignment Scoring")
	int32 InputSize = 1;

	/** Number of outputs (match/gap scores). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alignment Scoring")
	int32 OutputSize = 2;

	/** Runs the mock training routine using example data. */
	UFUNCTION(BlueprintCallable, Category = "Alignment Scoring")
	void SimulateTraining();

	/** Predicts scoring parameters from provided inputs. */
	UFUNCTION(BlueprintCallable, Category = "Alignment Scoring")
	TArray<float> PredictScoring(const TArray<float>& Inputs) const;
};
