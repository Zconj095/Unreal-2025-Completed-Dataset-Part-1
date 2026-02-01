#include "SpatialLSTMActor.h"

ASpatialLSTMActor::ASpatialLSTMActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASpatialLSTMActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<USpatialLSTMManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Spatial LSTM Manager (flattened input = 3 points * 2 = 6)
    Manager->InitializeLSTM(/*inputSize*/6, /*hiddenNeurons*/10, /*outputSize*/1);

    // Simulate Spatial Data
    Manager->AddSpatialData({ FVector2D(1.0, 2.0), FVector2D(3.0, 4.0), FVector2D(5.0, 6.0) }, { 0.5 });
    Manager->AddSpatialData({ FVector2D(2.0, 3.0), FVector2D(4.0, 5.0), FVector2D(6.0, 7.0) }, { 0.7 });
    Manager->AddSpatialData({ FVector2D(3.0, 4.0), FVector2D(5.0, 6.0), FVector2D(7.0, 8.0) }, { 0.9 });

    // Train Network
    const double FinalError = Manager->TrainLSTM(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Test Prediction
    const TArray<FVector2D> TestCoords = { FVector2D(4.0, 5.0), FVector2D(6.0, 7.0), FVector2D(8.0, 9.0) };
    const TArray<double> Prediction = Manager->Predict(TestCoords);

    FString PredStr;
    for (int i = 0; i < Prediction.Num(); ++i)
    {
        PredStr += FString::SanitizeFloat(Prediction[i]);
        if (i + 1 < Prediction.Num()) PredStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Prediction: %s"), *PredStr);
}

