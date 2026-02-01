#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalEnergyVisualizerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalEnergyVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalEnergyVisualizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Number of nodes along each axis of the grid. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Visualization", meta = (ClampMin = "1"))
	int32 GridSize = 10;

	/** World spacing between nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Visualization")
	float DeltaSpacing = 1.0f;

	/** Multiplier applied to the field when drawing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Visualization")
	float ScaleMultiplier = 0.5f;

	/** Whether to draw debug boxes at each sample. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Visualization")
	bool bDrawDebugNodes = true;

	/** Color used to draw debug nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Visualization")
	FColor NodeColor = FColor::Emerald;

	/** Lifetime of each debug box. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Energy Visualization")
	float DebugDuration = 8.0f;

	/** Cached total energy computed from the field. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy Visualization")
	float TotalBiochemicalEnergy = 0.0f;

	/** Recomputes the total energy based on the current field. */
	UFUNCTION(BlueprintCallable, Category = "Energy Visualization")
	float ComputeTotalBiochemicalEnergy();

private:
	TArray<float> MagicalField;

	void BuildMagicalField();
	int32 GetFlatIndex(int32 X, int32 Y, int32 Z) const;
	float SampleField(int32 X, int32 Y, int32 Z) const;
	float ComputeGradientMagnitude(int32 X, int32 Y, int32 Z) const;
	void DrawFieldDebug() const;
};
