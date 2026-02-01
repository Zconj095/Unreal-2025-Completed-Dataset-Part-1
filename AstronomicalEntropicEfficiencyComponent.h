#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstronomicalEntropicEfficiencyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAstronomicalEntropicEfficiencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAstronomicalEntropicEfficiencyComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** H: Total celestial information processed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entropic Efficiency")
	float TotalInformationProcessed = 10.0f;

	/** ΔS: Neural entropy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entropic Efficiency")
	float NeuralEntropy = 2.0f;

	/** η_s: Cached entropic efficiency result. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entropic Efficiency")
	float EntropicEfficiency = 0.0f;

	/** Calculates η_s = H / ΔS with zero-guarding. */
	UFUNCTION(BlueprintCallable, Category = "Entropic Efficiency")
	float CalculateEfficiency(float H, float DeltaS) const;

	/** Updates both parameters at once. */
	UFUNCTION(BlueprintCallable, Category = "Entropic Efficiency")
	void UpdateParameters(float NewTotalInformation, float NewNeuralEntropy);
};
