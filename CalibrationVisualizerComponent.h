#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CalibrationVisualizerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCalibrationVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCalibrationVisualizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration")
	FVector Deviation = FVector(0.1f, 0.2f, 0.3f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration")
	FVector Sensitivity = FVector(1.5f, 1.2f, 1.7f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calibration")
	UPrimitiveComponent* CalibrationIndicator = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Calibration")
	FVector Adjustment = FVector::ZeroVector;

	UFUNCTION(BlueprintCallable, Category = "Calibration")
	void ApplyCalibration();
};
