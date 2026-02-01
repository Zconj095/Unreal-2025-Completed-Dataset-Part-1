#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AetherialLobeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAetherialLobeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAetherialLobeComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Number of conceptual "Aetherial Threads" contributing to the state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aetherial Lobe", meta = (ClampMin = "1"))
	int32 NumThreads = 5;

	/** Size of each magic-state vector that contributes to the brain state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aetherial Lobe", meta = (ClampMin = "1"))
	int32 StateSize = 3;

	/** Normalized amplitudes for each thread. */
	UPROPERTY(VisibleAnywhere, Category = "Aetherial Lobe")
	TArray<float> Amplitudes;

	/** Flattened matrix of magic states ([[stateSize x NumThreads]]). */
	UPROPERTY(VisibleAnywhere, Category = "Aetherial Lobe")
	TArray<float> MagicStates;

	/** Computed brain state vector (|Ψ⟩). */
	UPROPERTY(VisibleAnywhere, Category = "Aetherial Lobe")
	TArray<float> BrainState;

	/** Rebuilds amplitudes, magic states, and recomputes |Ψ⟩. */
	UFUNCTION(BlueprintCallable, Category = "Aetherial Lobe")
	void RebuildAetherialState();

private:
	void GenerateRandomAmplitudes();
	void GenerateRandomMagicStates();
	void NormalizeAmplitudes();
	void ComputeBrainState();
	void LogBrainState() const;
};
