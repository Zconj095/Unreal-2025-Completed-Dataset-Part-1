#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtomicReconstructionEnergyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtomicReconstructionEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtomicReconstructionEnergyComponent();

	/** Calculates the total energy input for reconstruction. */
	UFUNCTION(BlueprintCallable, Category = "Atomic Reconstruction")
	float CalculateEnergyInput(float EnthalpyChange, float EntropyChange, float Temperature, float MagicalEnergy) const;
};
