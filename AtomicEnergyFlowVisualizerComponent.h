#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtomicEnergyFlowVisualizerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtomicEnergyFlowVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtomicEnergyFlowVisualizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Measured enthalpy changes used to visualize energy inputs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	TArray<float> EnthalpyChanges = { 500.f, 600.f, 700.f, 800.f };

	/** ΔS: Entropy change in Joules/Kelvin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	float EntropyChange = 0.02f;

	/** Temperature in Kelvin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	float Temperature = 300.0f;

	/** Magical energy term in Joules. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	float MagicalEnergy = 50.0f;

	/** Scale factor applied to the energy values when drawing debug bars. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	float ScaleFactor = 0.01f;

	/** Spacing between bars in game units. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	float BarSpacing = 200.0f;

	/** Toggle whether debug bars should be drawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	bool bDrawDebugBars = true;

	/** Lifetime of the debug boxes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Flow")
	float DebugDuration = 10.0f;

	/** Calculates energy input for a single enthalpy change. */
	UFUNCTION(BlueprintCallable, Category = "Atomic Flow")
	float CalculateEnergyInput(float EnthalpyChange) const;

	/** Logs each energy input besides drawing optional bars. */
	UFUNCTION(BlueprintCallable, Category = "Atomic Flow")
	void VisualizeEnergyFlow();
};
