#include "DifferentiationActor.h"

ADifferentiationActor::ADifferentiationActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ADifferentiationActor::BeginPlay()
{
    Super::BeginPlay();

    Manager = NewObject<UDifferentiationManager>(this);
    if (!ensure(Manager)) { return; }

    // Initialize Differentiation Manager
    Manager->InitializeNetwork(/*inputSize*/2, /*hiddenNeurons*/10, /*outputSize*/1);

    // Example vectors
    const TArray<double> V1 { 1.0, 2.0, 3.0 };
    const TArray<double> V2 { 2.0, 4.0, 6.0 };
    const TArray<double> V3 { 1.0, 0.0, -1.0 };

    // Display Differentiation Results
    Manager->DisplayDifferentiationResults(V1, V2);
    Manager->DisplayDifferentiationResults(V1, V3);
}

