#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BondEnergyVisualizerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBondEnergyVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBondEnergyVisualizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Wavelengths in meters used for visualization. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond Energy Visualization")
	TArray<float> Wavelengths = { 4.0e-7f, 5.0e-7f, 6.0e-7f, 7.0e-7f };

	/** Scaling multiplier applied to bond energy when drawing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond Energy Visualization")
	float ScaleFactor = 1e19f;

	/** Spacing between visual bars. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond Energy Visualization")
	float BarSpacing = 200.0f;

	/** Whether to draw debug bars at run-time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond Energy Visualization")
	bool bDrawDebugBars = true;

	/** Lifetime of the debug visuals in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond Energy Visualization")
	float DebugDuration = 10.0f;

	/** Logs each computed bond energy. */
	UFUNCTION(BlueprintCallable, Category = "Bond Energy Visualization")
	void VisualizeBondEnergies();

	/** Computes bond dissociation energy E_b = hc / λ. */
	UFUNCTION(BlueprintCallable, Category = "Bond Energy Visualization")
	float CalculateBondEnergy(float Wavelength) const;
};
