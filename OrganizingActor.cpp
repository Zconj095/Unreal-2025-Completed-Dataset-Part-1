#include "OrganizingActor.h"

AOrganizingActor::AOrganizingActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AOrganizingActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UOrganizingManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Organizing Manager
    Manager->InitializeNetwork(/*inputSize*/3, /*hiddenNeurons*/10, /*outputSize*/3);

    // Data for organization
    TArray<FDoubleArray> Data;
    {
        FDoubleArray A; A.Values = { 1.0, 2.0, 3.0 }; Data.Add(A);
        FDoubleArray B; B.Values = { 4.0, 5.0, 6.0 }; Data.Add(B);
        FDoubleArray C; C.Values = { 7.0, 8.0, 9.0 }; Data.Add(C);
        FDoubleArray D; D.Values = { 10.0, 11.0, 12.0 }; Data.Add(D);
    }

    // Group IDs using a simple mapping function: static cast<int>(item[0]) % 2
    TArray<int32> GroupIDs;
    GroupIDs.Reserve(Data.Num());
    for (const FDoubleArray& Item : Data)
    {
        const int32 G = static_cast<int32>((Item.Values.Num() > 0) ? static_cast<int32>(Item.Values[0]) % 2 : 0);
        GroupIDs.Add(G);
    }

    // Organize data
    Manager->OrganizeData(Data, GroupIDs);

    // Display organized groups
    Manager->DisplayGroups();

    // Train neural network
    Manager->TrainNetwork(Data, GroupIDs, /*epochs*/1000, /*lr*/0.01);

    // Predict group for new data
    TArray<double> NewData = { 5.0, 6.0, 7.0 };
    const int32 PredictedGroup = Manager->PredictGroup(NewData);
    UE_LOG(LogTemp, Log, TEXT("Predicted Group for 5,6,7: %d"), PredictedGroup);
}
