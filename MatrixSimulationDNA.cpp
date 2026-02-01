#include "MatrixSimulationDNA.h"

AMatrixSimulationDNA::AMatrixSimulationDNA()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationDNA::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Automated Matrix Simulation DNA System Initialized."));
}

void AMatrixSimulationDNA::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment the task timer
    TaskTimer += DeltaSeconds;

    // Perform automated tasks at regular intervals
    if (TaskTimer >= TaskInterval)
    {
        PerformAutomatedTasks();
        TaskTimer = 0.f; // Reset the timer
    }
}

int32 AMatrixSimulationDNA::FindSpeciesIndex(const FString& Species) const
{
    for (int32 i = 0; i < GeneticDatabase.Num(); ++i)
    {
        if (GeneticDatabase[i].Species == Species)
        {
            return i;
        }
    }
    return INDEX_NONE;
}

void AMatrixSimulationDNA::AddSpecies(const FString& Species)
{
    if (FindSpeciesIndex(Species) != INDEX_NONE)
    {
        UE_LOG(LogTemp, Warning, TEXT("Species '%s' already exists in the database."), *Species);
        return;
    }

    FGeneticData NewGeneticData(Species);
    GeneticDatabase.Add(MoveTemp(NewGeneticData));
    UE_LOG(LogTemp, Log, TEXT("Species Added - %s"), *Species);
}

void AMatrixSimulationDNA::AddGeneToSpecies(const FString& Species, const FString& GeneKey, const FString& GeneValue)
{
    const int32 Index = FindSpeciesIndex(Species);
    if (GeneticDatabase.IsValidIndex(Index))
    {
        GeneticDatabase[Index].AddGene(GeneKey, GeneValue);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Species '%s' not found."), *Species);
    }
}

void AMatrixSimulationDNA::CloneGeneticData(const FString& SourceSpecies, const FString& TargetSpecies)
{
    const int32 SourceIndex = FindSpeciesIndex(SourceSpecies);
    if (!GeneticDatabase.IsValidIndex(SourceIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("Source species '%s' not found."), *SourceSpecies);
        return;
    }

    // Ensure target exists
    AddSpecies(TargetSpecies);
    const int32 TargetIndex = FindSpeciesIndex(TargetSpecies);
    if (!GeneticDatabase.IsValidIndex(TargetIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("Target species '%s' could not be added/found."), *TargetSpecies);
        return;
    }

    // Copy genes
    for (const TPair<FString, FString>& Pair : GeneticDatabase[SourceIndex].Genes)
    {
        GeneticDatabase[TargetIndex].AddGene(Pair.Key, Pair.Value);
    }

    UE_LOG(LogTemp, Log, TEXT("Genetic Data Cloned - Source: %s, Target: %s"), *SourceSpecies, *TargetSpecies);
}

void AMatrixSimulationDNA::DisplayAllGeneticData() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying genetic data for all species..."));
    for (const FGeneticData& Data : GeneticDatabase)
    {
        Data.DisplayGenes();
    }
}

void AMatrixSimulationDNA::PerformAutomatedTasks()
{
    UE_LOG(LogTemp, Log, TEXT("Performing automated DNA tasks..."));

    // Add species dynamically
    const FString SpeciesName = FString::Printf(TEXT("AutomatedSpecies%d"), GeneticDatabase.Num());
    AddSpecies(SpeciesName);

    // Add genetic traits to the most recently added species
    if (GeneticDatabase.Num() > 0)
    {
        const int32 TraitNum = FMath::RandRange(1, 9); // Unity int Range(1,10) -> 1..9
        const int32 ValueNum = FMath::RandRange(1, 99); // Unity int Range(1,100) -> 1..99
        AddGeneToSpecies(SpeciesName, FString::Printf(TEXT("Trait%d"), TraitNum), FString::Printf(TEXT("Value%d"), ValueNum));
    }

    // Clone the first species to a new one if possible
    if (GeneticDatabase.Num() >= 2)
    {
        const int32 CloneNum = FMath::RandRange(1, 99); // Unity int Range(1,100) -> 1..99
        CloneGeneticData(GeneticDatabase[0].Species, FString::Printf(TEXT("Cloned%d"), CloneNum));
    }

    // Display current genetic database
    DisplayAllGeneticData();
}

