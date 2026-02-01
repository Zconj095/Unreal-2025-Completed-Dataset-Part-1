#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BondEnergyCalculatorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBondEnergyCalculatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBondEnergyCalculatorComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Wavelength in meters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bond Energy")
	float Wavelength = 5.0e-7f;

	/** Calculated bond dissociation energy. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bond Energy")
	float BondEnergy = 0.0f;

	/** Computes E_b = h·c / λ. */
	UFUNCTION(BlueprintCallable, Category = "Bond Energy")
	float CalculateBondEnergy(float WavelengthValue) const;
};
