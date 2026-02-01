#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationAnalysisPrompt.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationAnalysisPrompt : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationAnalysisPrompt();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Analysis")
    void AddDosageFeed(float FrequencyRating);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Analysis")
    void RetrieveFeedStatus() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float SafeFeedInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float UnsafeFeedInterval = 7.f; // seconds

private:
    struct FDosageFeed
    {
        FString FeedID;
        float FrequencyRating = 0.f; // Hz
        bool bIsSafe = true;

        explicit FDosageFeed(float InFrequency)
            : FeedID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , FrequencyRating(InFrequency)
            , bIsSafe(InFrequency <= 76.f)
        {
        }
        FDosageFeed() = default;
    };

    void AnalyzeFeed(const FDosageFeed& Feed);
    void ActivateHealthProtocol82();
    void PurifySystem();
    void EjectUser();

    // Data
    TArray<FDosageFeed> DosageFeeds;
    bool bHealthProtocolActive = false;

    // Timer
    float FeedAdditionTimer = 0.f;
};

