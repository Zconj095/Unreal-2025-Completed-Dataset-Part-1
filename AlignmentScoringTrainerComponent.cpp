#include "AlignmentScoringTrainerComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UAlignmentScoringTrainerComponent::UAlignmentScoringTrainerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAlignmentScoringTrainerComponent::BeginPlay()
{
	Super::BeginPlay();

	SimulateTraining();
}

void UAlignmentScoringTrainerComponent::SimulateTraining()
{
	const TArray<TArray<float>> TrainingInputs = {
		{1.0f},
		{2.0f}
	};

	const TArray<TArray<float>> TrainingOutputs = {
		{2.0f, 1.0f},
		{1.5f, 0.5f}
	};

	const int32 NumEpochs = 1000;
	for (int32 Epoch = 0; Epoch < NumEpochs; Epoch += 100)
	{
		UE_LOG(LogTemp, Log, TEXT("Epoch %d/%d simulated, sample error: %0.4f"), Epoch + 1, NumEpochs, 0.1f);
	}

	const TArray<float> TestInput = {1.5f};
	const TArray<float> Predicted = PredictScoring(TestInput);
	if (Predicted.Num() >= 2)
	{
		UE_LOG(LogTemp, Log, TEXT("Predicted Scores: Match=%0.4f, Gap=%0.4f"), Predicted[0], Predicted[1]);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Predicted Scores incomplete."));
	}
}

TArray<float> UAlignmentScoringTrainerComponent::PredictScoring(const TArray<float>& Inputs) const
{
	TArray<float> Result;
	Result.Init(0.0f, OutputSize);

	if (Inputs.Num() == 0 || OutputSize <= 0)
	{
		return Result;
	}

	float SumInput = 0.0f;
	for (float Value : Inputs)
	{
		SumInput += Value;
	}
	const float Normalized = SumInput / Inputs.Num();

	for (int32 Index = 0; Index < OutputSize; ++Index)
	{
		const float Offset = 0.5f * (Index + 1);
		Result[Index] = Normalized + Offset;
	}

	return Result;
}
