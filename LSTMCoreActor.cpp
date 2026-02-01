#include "LSTMCoreActor.h"

ALSTMCoreActor::ALSTMCoreActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ALSTMCoreActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<ULSTMMemoryManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize LSTM Memory Manager (feedforward stand-in)
    Manager->InitializeLSTM(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/1);

    // Add Memory Sequences
    Manager->AddMemorySequence(TArray<double>{1.0, 2.0, 3.0}, TArray<double>{0.5});
    Manager->AddMemorySequence(TArray<double>{2.0, 3.0, 4.0}, TArray<double>{0.7});
    Manager->AddMemorySequence(TArray<double>{3.0, 4.0, 5.0}, TArray<double>{0.9});

    // Train Network
    const double FinalError = Manager->TrainLSTM(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Test Prediction
    const TArray<double> TestInput { 4.0, 5.0, 6.0 };
    const TArray<double> Pred = Manager->PredictSequence(TestInput);
    if (Pred.Num() > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Prediction for Input [4,5,6]: %f"), Pred[0]);
    }
}

