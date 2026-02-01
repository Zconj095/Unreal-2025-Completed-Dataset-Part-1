#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalMagicalEnergyModelComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalMagicalEnergyModelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalMagicalEnergyModelComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Grid size along each axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magical Energy")
	int32 GridSize = 10;

	/** Spacing between samples. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magical Energy")
	float DeltaSpacing = 1.0f;

	/** Whether to log the final energy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magical Energy")
	bool bLogEnergy = true;

	/** Computed total biochemical energy. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magical Energy")
	float TotalBiochemicalEnergy = 0.0f;

private:
	TArray<float> MagicalField;

	void BuildField();
	int32 GetFlatIndex(int32 X, int32 Y, int32 Z) const;
	float SampleField(int32 X, int32 Y, int32 Z) const;
	float ComputeGradientMagnitude(int32 X, int32 Y, int32 Z) const;
};
