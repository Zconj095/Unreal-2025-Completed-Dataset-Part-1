#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttenuationPredictorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAttenuationPredictorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttenuationPredictorComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Initial intensity values per sample. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attenuation")
	TArray<float> InitialIntensities = { 100.f, 200.f };

	/** Distances corresponding to each sample. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attenuation")
	TArray<float> Distances = { 50.f, 40.f };

	/** Mock predicted attenuation coefficient. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attenuation")
	float PredictedCoefficient = 0.0f;

	/** Predicts attenuation based on the current heuristics. */
	UFUNCTION(BlueprintCallable, Category = "Attenuation")
	float Predict(float Intensity, float Distance) const;
};
