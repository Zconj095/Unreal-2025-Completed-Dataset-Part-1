#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AethericSynapseTransmissionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAethericSynapseTransmissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAethericSynapseTransmissionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** α: Scaling factor for synaptic efficiency. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synapse")
	float Alpha = 1.0f;

	/** β: Dissipation coefficient. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synapse")
	float Beta = 0.5f;

	/** Input from the magical cognitive region. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synapse")
	float MagicInput = 1.0f;

	/** Input from the logical cognitive region. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synapse")
	float ScienceInput = 1.0f;

	/** Calculates the synaptic transmission probability. */
	UFUNCTION(BlueprintCallable, Category = "Synapse")
	float CalculateSynapseTransmission(float Magic, float Science, float AlphaValue, float BetaValue) const;
};
