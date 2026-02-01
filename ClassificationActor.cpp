#include "ClassificationActor.h"

AClassificationActor::AClassificationActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AClassificationActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UClassificationManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Classification Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/3);
    Manager->InitializeKMeans(/*clusterCount*/3);

    // Simulate Data for Classification
    Manager->AddClassificationData(TArray<double> { 1.0, 2.0, 3.0 }, 0);
    Manager->AddClassificationData(TArray<double> { 4.0, 5.0, 6.0 }, 1);
    Manager->AddClassificationData(TArray<double> { 7.0, 8.0, 9.0 }, 2);

    // Train Neural Network
    const double FinalError = Manager->TrainNetwork(/*epochs*/1000, /*lr*/0.01);
    UE_LOG(LogTemp, Log, TEXT("Final Training Error: %f"), FinalError);

    // Predict Classification for New Data
    const int32 PredLabel = Manager->PredictLabel(TArray<double> { 3.0, 4.0, 5.0 });
    UE_LOG(LogTemp, Log, TEXT("Predicted Label (Neural Network): %d"), PredLabel);

    // Train KMeans Clustering
    {
        TArray<FDoubleArray> KMeansData; KMeansData.SetNum(3);
        KMeansData[0].Values = {1.0, 2.0, 3.0};
        KMeansData[1].Values = {4.0, 5.0, 6.0};
        KMeansData[2].Values = {7.0, 8.0, 9.0};
        Manager->TrainKMeans(KMeansData);
    }

    // Predict Cluster for New Data
    const int32 PredCluster = Manager->PredictCluster(TArray<double> { 3.0, 4.0, 5.0 });
    UE_LOG(LogTemp, Log, TEXT("Predicted Cluster (KMeans): %d"), PredCluster);
}
