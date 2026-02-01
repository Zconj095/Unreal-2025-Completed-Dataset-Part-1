#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AetherialLobeSector2Component.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAetherialLobeSector2Component : public UActorComponent
{
	GENERATED_BODY()

public:
	UAetherialLobeSector2Component();

protected:
	virtual void BeginPlay() override;

public:
	/** Number of basis threads. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aetherial Sector")
	int32 NumThreads = 5;

	/** Dimensionality of each thread state. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aetherial Sector")
	int32 StateSize = 4;

	/** Normalized amplitudes for each thread. */
	UPROPERTY(VisibleAnywhere, Category = "Aetherial Sector")
	TArray<float> Amplitudes;

	/** Flattened basis thread data (StateSize x NumThreads). */
	UPROPERTY(VisibleAnywhere, Category = "Aetherial Sector")
	TArray<float> BasisThreads;

	/** Resulting brain state vector. */
	UPROPERTY(VisibleAnywhere, Category = "Aetherial Sector")
	TArray<float> BrainState;

	/** Rebuilds random amplitudes and basis threads before computing |Ψ⟩. */
	UFUNCTION(BlueprintCallable, Category = "Aetherial Sector")
	void RebuildAetherialState();

private:
	void GenerateRandomAmplitudes();
	void GenerateRandomBasisThreads();
	void NormalizeAmplitudes();
	void ComputeBrainState();
	void LogBrainState() const;
};
