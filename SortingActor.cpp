#include "SortingActor.h"

ASortingActor::ASortingActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASortingActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<USortingManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Sorting Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/3);

    // Simulate Sorting Data
    Manager->AddSortingData({ 3.0, 1.0, 2.0 });
    Manager->AddSortingData({ 5.0, 4.0, 6.0 });
    Manager->AddSortingData({ 7.0, 9.0, 8.0 });

    // Train Neural Network
    Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);

    // Predict Sorted Order for New Data
    const TArray<double> Predicted = Manager->PredictSortedOrder({ 4.0, 2.0, 3.0 });
    FString PredStr;
    for (int i = 0; i < Predicted.Num(); ++i)
    {
        PredStr += FString::SanitizeFloat(Predicted[i]);
        if (i + 1 < Predicted.Num()) PredStr += TEXT(", ");
    }
    UE_LOG(LogTemp, Log, TEXT("Predicted Sorted Order: %s"), *PredStr);

    // Calculate Sorting Complexity
    const int32 N = 3;
    const double Complexity = Manager->CalculateComplexity(N);
    UE_LOG(LogTemp, Log, TEXT("Sorting Complexity for %d elements: O(%0.1f)"), N, Complexity);
}

