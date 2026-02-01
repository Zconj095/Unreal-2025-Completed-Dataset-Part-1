#include "FilteringActor.h"

AFilteringActor::AFilteringActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AFilteringActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UFilteringManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Filtering Manager
    Manager->InitializeNetwork(/*inputSize*/1, /*hiddenNeurons*/5, /*outputSize*/1);

    // Example Data
    const TArray<double> Data1 { 1.0, 2.5, 3.0, 4.5, 5.0 };
    const TArray<double> Data2 { 10.0, 20.0, 15.0, 25.0, 30.0 };

    // Predicates
    auto GreaterThanThree = [](double x) { return x > 3.0; };
    auto EvenNumbers = [](double x) { return FMath::Fmod(x, 2.0) == 0.0; };

    // Apply Filters
    Manager->AddFilteringData(Data1, GreaterThanThree);
    Manager->AddFilteringData(Data2, EvenNumbers);

    // Train Neural Network for Predictive Filtering
    TArray<FDoubleArray> TrainX; TrainX.SetNum(4);
    TrainX[0].Values = {1.0};
    TrainX[1].Values = {2.5};
    TrainX[2].Values = {3.0};
    TrainX[3].Values = {4.5};
    TArray<FDoubleArray> TrainY; TrainY.SetNum(4);
    TrainY[0].Values = {0.0};
    TrainY[1].Values = {0.0};
    TrainY[2].Values = {1.0};
    TrainY[3].Values = {1.0};
    Manager->TrainNetwork(TrainX, TrainY, /*epochs*/1000, /*lr*/0.01);

    // Predict Filtering with Neural Network
    const double Predicted = Manager->Predict(TArray<double>{4.0});
    UE_LOG(LogTemp, Log, TEXT("Predicted Result for 4.0: %s"), (Predicted > 0.5 ? TEXT("Included") : TEXT("Excluded")));

    // Display Filtered Results
    Manager->DisplayFilteredResults();
}
