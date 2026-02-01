#include "MemoryCategorizationActor.h"

AMemoryCategorizationActor::AMemoryCategorizationActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AMemoryCategorizationActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UMemoryCategorizationManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Categorization Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/3);

    // Simulate Memory Data
    Manager->AddMemoryData(TArray<double>{1.0, 2.0, 3.0}, 0);
    Manager->AddMemoryData(TArray<double>{2.0, 3.0, 4.0}, 1);
    Manager->AddMemoryData(TArray<double>{3.0, 4.0, 5.0}, 2);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Category for New Features
    const int32 PredictedCategory = Manager->PredictCategory(TArray<double>{4.0, 5.0, 6.0});
    UE_LOG(LogTemp, Log, TEXT("Predicted Category for Features [4,5,6]: %d"), PredictedCategory);

    // Display Category Statistics (percentages)
    const TMap<int32, double> Stats = Manager->GetCategoryStatistics();
    for (const TPair<int32, double>& KV : Stats)
    {
        UE_LOG(LogTemp, Log, TEXT("Category %d: %f%% of entries"), KV.Key, KV.Value);
    }
}

