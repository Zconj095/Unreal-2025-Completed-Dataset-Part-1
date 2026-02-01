#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationAnalyzer.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationAnalyzer : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationAnalyzer();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Analyzer")
    void CollectSimulationData(const FString& Content);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Analyzer")
    void RetrieveCollectedData() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float DataCollectionInterval = 3.f; // seconds

private:
    struct FSimulationData
    {
        FString DataID;
        FString Content;

        explicit FSimulationData(const FString& InContent)
            : DataID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , Content(InContent)
        {
        }
        FSimulationData() = default;
    };

    void ProcessData(const FSimulationData& Data);
    void SendToMainframe(const FSimulationData& Data);
    void StoreData(const FSimulationData& Data);

    // Data store
    TArray<FSimulationData> CollectedData;

    // Timer
    float DataCollectionTimer = 0.f;
};

