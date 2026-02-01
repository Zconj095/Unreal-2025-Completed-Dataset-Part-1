#include "SimilarityActor.h"

ASimilarityActor::ASimilarityActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASimilarityActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<USimilarityManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Similarity Manager
    Manager->InitializeNetwork(/*inputSize*/2, /*hiddenNeurons*/10, /*outputSize*/1);

    // Example Data
    const TArray<double> Vector1 = { 1.0, 2.0, 3.0 };
    const TArray<double> Vector2 = { 2.0, 4.0, 6.0 };
    const TArray<double> Vector3 = { 1.0, 0.0, -1.0 };

    // Add Similarity Data
    Manager->AddSimilarityData(Vector1, Vector2);
    Manager->AddSimilarityData(Vector1, Vector3);

    // Display Similarity Data
    Manager->DisplaySimilarities();

    // Additional Similarity Metrics
    const double Dist12 = Manager->CalculateEuclideanDistance(Vector1, Vector2);
    UE_LOG(LogTemp, Log, TEXT("Euclidean Distance between Vector1 and Vector2: %f"), Dist12);
}

