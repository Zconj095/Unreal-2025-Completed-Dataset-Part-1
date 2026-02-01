#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ArcaneNeuralTuringMachineComponent.generated.h"

UENUM(BlueprintType)
enum class EArcaneTuringAction : uint8
{
	None,
	Write,
	MoveLeft,
	MoveRight
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UArcaneNeuralTuringMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UArcaneNeuralTuringMachineComponent();

protected:
	virtual void BeginPlay() override;

private:
	void InitializeMachine();
	TArray<float> Tape;
	TArray<float> CurrentState;
	int32 HeadPosition = 0;

	void PerformDemoSteps();
	void Step(EArcaneTuringAction Action);
	TArray<float> TransitionFunction(float Symbol) const;
	void LogMachineState() const;
	float ComputeStateNorm(const TArray<float>& State) const;
	void SimulateTraining() const;

public:
	/** Number of symbols stored on the tape. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcane Turing")
	int32 TapeSize = 10;

	/** Dimensionality of the internal state vector. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcane Turing")
	int32 StateSize = 3;

	/** Number of demo actions to run during BeginPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcane Turing")
	TArray<EArcaneTuringAction> DemoActions = {EArcaneTuringAction::Write, EArcaneTuringAction::MoveRight, EArcaneTuringAction::Write, EArcaneTuringAction::MoveLeft};
};
