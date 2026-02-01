#include "CalibrationVisualizerComponent.h"
#include "Logging/LogMacros.h"

UCalibrationVisualizerComponent::UCalibrationVisualizerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCalibrationVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
	ApplyCalibration();
}

void UCalibrationVisualizerComponent::ApplyCalibration()
{
	Adjustment = FVector(Deviation.X * Sensitivity.X, Deviation.Y * Sensitivity.Y, Deviation.Z * Sensitivity.Z);

	if (CalibrationIndicator)
	{
		CalibrationIndicator->SetWorldScale3D(Adjustment);
	}

	UE_LOG(LogTemp, Log, TEXT("Calibration adjustment: %s"), *Adjustment.ToString());
}
