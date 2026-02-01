// ... probable header
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CellularEnergyProductionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCellularEnergyProductionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCellularEnergyProductionComponent();

protected:
	virtual void BeginPlay() override;

private:
	double CalculateATPProduction() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metabolism", meta=(ClampMin="0.0"))
	float Vmax = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metabolism", meta=(ClampMin="0.0"))
	float K_ADP = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metabolism", meta=(ClampMin="0.0"))
	float K_Pi = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metabolism", meta=(ClampMin="0.0"))
	float ADP = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metabolism", meta=(ClampMin="0.0"))
	float Pi = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Metabolism", meta=(ClampMin="0.0"))
	float MagicalEnergy = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Metabolism")
	float ATPProductionRate = 0.0f;
};
