#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationDNA.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationDNA : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationDNA();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation DNA")
    void AddSpecies(const FString& Species);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation DNA")
    void AddGeneToSpecies(const FString& Species, const FString& GeneKey, const FString& GeneValue);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation DNA")
    void CloneGeneticData(const FString& SourceSpecies, const FString& TargetSpecies);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation DNA")
    void DisplayAllGeneticData() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float TaskInterval = 5.f; // seconds

private:
    struct FGeneticData
    {
        FString Species;
        TMap<FString, FString> Genes; // key -> value

        explicit FGeneticData(const FString& InSpecies)
            : Species(InSpecies)
        {}
        FGeneticData() = default;

        void AddGene(const FString& GeneKey, const FString& GeneValue)
        {
            Genes.Add(GeneKey, GeneValue);
            UE_LOG(LogTemp, Log, TEXT("Gene Added - Species: %s, Gene: %s = %s"), *Species, *GeneKey, *GeneValue);
        }

        void EditGene(const FString& GeneKey, const FString& NewGeneValue)
        {
            if (Genes.Contains(GeneKey))
            {
                Genes[GeneKey] = NewGeneValue;
                UE_LOG(LogTemp, Log, TEXT("Gene Edited - Species: %s, Gene: %s = %s"), *Species, *GeneKey, *NewGeneValue);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Gene '%s' not found in species '%s'."), *GeneKey, *Species);
            }
        }

        void DisplayGenes() const
        {
            UE_LOG(LogTemp, Log, TEXT("Genes for Species: %s"), *Species);
            for (const TPair<FString, FString>& Pair : Genes)
            {
                UE_LOG(LogTemp, Log, TEXT("  %s = %s"), *Pair.Key, *Pair.Value);
            }
        }
    };

    int32 FindSpeciesIndex(const FString& Species) const;
    void PerformAutomatedTasks();

    // Database of all species
    TArray<FGeneticData> GeneticDatabase;

    // Timer
    float TaskTimer = 0.f;
};

