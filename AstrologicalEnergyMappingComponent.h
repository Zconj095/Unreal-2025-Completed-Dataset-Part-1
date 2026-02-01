#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstrologicalEnergyMappingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAstrologicalEnergyMappingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAstrologicalEnergyMappingComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Total energy influence computed from the configured celestial data. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Astrological Energy")
	float TotalEnergyInfluence = 0.0f;

	/** Magnitudes of celestial influences (alpha_i). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Astrological Energy")
	TArray<float> GalacticMagnitudes = { 100.f, 200.f, 150.f };

	/** Distances of celestial bodies (d_i). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Astrological Energy")
	TArray<float> CelestialDistances = { 2.f, 5.f, 3.f };

	/** Calculates the sum of (alpha_i / d_i^2) using the current arrays. */
	UFUNCTION(BlueprintCallable, Category = "Astrological Energy")
	float CalculateAstrologicalEnergy() const;

	/** Logs a placeholder neural-network prediction for the sum. */
	UFUNCTION(BlueprintCallable, Category = "Astrological Energy")
	void LogNeuralNetworkPlaceholder() const;

	/** Logs a placeholder TensorFlow computation for the sum. */
	UFUNCTION(BlueprintCallable, Category = "Astrological Energy")
	void LogTensorFlowPlaceholder() const;

private:
	float CalculateEnergy(const TArray<float>& Magnitudes, const TArray<float>& Distances) const;
	TArray<float> BuildFlattenedInput() const;
};
