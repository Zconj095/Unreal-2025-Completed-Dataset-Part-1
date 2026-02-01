#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtmosphericPressureModelingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtmosphericPressureModelingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtmosphericPressureModelingComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Atmospheric pressure gradient (∇P). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atmospheric Pressure")
	FVector2D PressureGradient = FVector2D(10.0f, -5.0f);

	/** Air density (ρ). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atmospheric Pressure")
	float AirDensity = 1.225f;

	/** Resulting pressure gradient force. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Atmospheric Pressure")
	FVector2D PressureForce = FVector2D::ZeroVector;

	/** Computes Fp = -(1 / ρ) * ∇P while guarding zero density. */
	UFUNCTION(BlueprintCallable, Category = "Atmospheric Pressure")
	FVector2D CalculatePressureForce(const FVector2D& Gradient, float Density) const;

	/** Logs a mock neural network prediction. */
	UFUNCTION(BlueprintCallable, Category = "Atmospheric Pressure")
	void LogNeuralNetworkPlaceholder() const;

	/** Logs a mock TensorFlow computation. */
	UFUNCTION(BlueprintCallable, Category = "Atmospheric Pressure")
	void LogTensorFlowPlaceholder() const;
};
