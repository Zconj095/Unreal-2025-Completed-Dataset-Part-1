#include "MatrixSimulationAnalysisPrompt.h"

#include "Misc/Guid.h"

AMatrixSimulationAnalysisPrompt::AMatrixSimulationAnalysisPrompt()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimulationAnalysisPrompt::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Simulation Analysis Prompt Initialized."));
}

void AMatrixSimulationAnalysisPrompt::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timers
    FeedAdditionTimer += DeltaSeconds;

    // Automate safe feed addition (mirrors Unity order and reset behavior)
    if (FeedAdditionTimer >= SafeFeedInterval)
    {
        AddDosageFeed(FMath::FRandRange(50.f, 75.f)); // Safe frequency
        FeedAdditionTimer = 0.f; // Reset timer
    }

    // Automate unsafe feed addition using same timer (like Unity sample)
    if (FeedAdditionTimer >= UnsafeFeedInterval)
    {
        AddDosageFeed(FMath::FRandRange(77.f, 100.f)); // Unsafe frequency
        FeedAdditionTimer = 0.f; // Reset timer
    }
}

void AMatrixSimulationAnalysisPrompt::AddDosageFeed(float FrequencyRating)
{
    FDosageFeed Feed(FrequencyRating);
    DosageFeeds.Add(Feed);

    UE_LOG(LogTemp, Log, TEXT("Dosage Feed Added - ID: %s, Frequency: %.2f Hz, Safe: %s"), *Feed.FeedID, FrequencyRating, Feed.bIsSafe ? TEXT("true") : TEXT("false"));
    AnalyzeFeed(Feed);
}

void AMatrixSimulationAnalysisPrompt::AnalyzeFeed(const FDosageFeed& Feed)
{
    if (!Feed.bIsSafe)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unsafe dosage detected! Frequency: %.2f Hz."), Feed.FrequencyRating);
        ActivateHealthProtocol82();
    }
}

void AMatrixSimulationAnalysisPrompt::ActivateHealthProtocol82()
{
    if (bHealthProtocolActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("Health Protocol 82 is already active."));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Activating Health Protocol 82..."));
    bHealthProtocolActive = true;

    // Simulate Purification Frequency 76 Class A
    PurifySystem();
}

void AMatrixSimulationAnalysisPrompt::PurifySystem()
{
    UE_LOG(LogTemp, Log, TEXT("Initiating Purification Frequency 76 Class A..."));
    DosageFeeds.Reset();
    UE_LOG(LogTemp, Log, TEXT("Purification complete. All dosage feeds wiped from the system for the last 72 hours."));

    // Simulate user ejection
    EjectUser();
}

void AMatrixSimulationAnalysisPrompt::EjectUser()
{
    UE_LOG(LogTemp, Warning, TEXT("User has been ejected from the system. Awaiting further notice from the HeadAdmin team."));
}

void AMatrixSimulationAnalysisPrompt::RetrieveFeedStatus() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving dosage feed statuses..."));
    for (const FDosageFeed& Feed : DosageFeeds)
    {
        UE_LOG(LogTemp, Log, TEXT("Feed - ID: %s, Frequency: %.2f Hz, Safe: %s"), *Feed.FeedID, Feed.FrequencyRating, Feed.bIsSafe ? TEXT("true") : TEXT("false"));
    }

    if (DosageFeeds.Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("No active dosage feeds in the system."));
    }
}

