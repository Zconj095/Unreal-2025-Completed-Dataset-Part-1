#include "TemporalLSTMActor.h"

ATemporalLSTMActor::ATemporalLSTMActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ATemporalLSTMActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UTemporalLSTMManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Temporal LSTM Manager
    Manager->InitializeLSTM(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Temporal Data
    Manager->AddTemporalData({ 1.0, 2.0, 3.0 }, { 0.5 });
    Manager->AddTemporalData({ 2.0, 3.0, 4.0 }, { 0.7 });
    Manager->AddTemporalData({ 3.0, 4.0, 5.0 }, { 0.9 });

    // Train LSTM Network
    const double FinalError = Manager->TrainLSTM(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Test Prediction
    const TArray<double> TestInput = { 4.0, 5.0, 6.0 };
    const TArray<double> Prediction = Manager->Predict(TestInput);
    FString PredStr;
    for (int i = 0; i < Prediction.Num(); ++i)
    {
        PredStr += FString::SanitizeFloat(Prediction[i]);
        if (i + 1 < Prediction.Num()) PredStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Prediction for Input 4,5,6: %s"), *PredStr);

    // Evaluate Average Prediction Error
    TArray<FDoubleArray> TestInputs;
    {
        FDoubleArray A; A.Values = { 1.0, 2.0, 3.0 }; TestInputs.Add(A);
        FDoubleArray B; B.Values = { 2.0, 3.0, 4.0 }; TestInputs.Add(B);
        FDoubleArray C; C.Values = { 3.0, 4.0, 5.0 }; TestInputs.Add(C);
    }

    TArray<FDoubleArray> TestOutputs;
    {
        FDoubleArray A; A.Values = { 0.5 }; TestOutputs.Add(A);
        FDoubleArray B; B.Values = { 0.7 }; TestOutputs.Add(B);
        FDoubleArray C; C.Values = { 0.9 }; TestOutputs.Add(C);
    }

    const double AvgErr = Manager->CalculateAveragePredictionError(TestInputs, TestOutputs);
    UE_LOG(LogTemp, Log, TEXT("Average Prediction Error: %f"), AvgErr);
}
