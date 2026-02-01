#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainCoolingEfficiencyComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBrainCoolingEfficiencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBrainCoolingEfficiencyComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooling")
	float ThermalConductivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooling")
	float WaterTemperature = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooling")
	float SurfaceArea = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooling")
	float TemperatureGradient = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooling")
	float CoolingEfficiency = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Cooling")
	float CalculateCoolingEfficiency(float Conductivity, float Temperature, float Area, float Gradient) const;
};
