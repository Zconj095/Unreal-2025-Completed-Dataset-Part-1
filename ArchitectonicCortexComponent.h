#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArchitectonicCortexComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UArchitectonicCortexComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UArchitectonicCortexComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Number of inputs interpreted by the blueprint generator. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architectonic Cortex")
	int32 InputSize = 10;

	/** Hidden layer sizes (informational only). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architectonic Cortex")
	TArray<int32> HiddenLayers = { 15, 20 };

	/** Number of outputs expected from the conceptual network. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architectonic Cortex")
	int32 OutputSize = 125;

	/** Resolution per axis of the holographic blueprint cube. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architectonic Cortex")
	int32 BlueprintDimension = 5;

	/** Whether to log the blueprint values at runtime. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Architectonic Cortex")
	bool bLogBlueprint = true;

	/** Stores the generated blueprint values (dimension^3 entries). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Architectonic Cortex")
	TArray<float> BlueprintData;

	/** Rebuilds the holographic blueprint from the provided inputs. */
	UFUNCTION(BlueprintCallable, Category = "Architectonic Cortex")
	void GenerateBlueprint(const TArray<float>& Inputs);

private:
	void ResetBlueprint();
	void LogBlueprint() const;
	float SampleBlueprintValue(const TArray<float>* Inputs, int32 Index) const;
	void SimulateTraining() const;
};
