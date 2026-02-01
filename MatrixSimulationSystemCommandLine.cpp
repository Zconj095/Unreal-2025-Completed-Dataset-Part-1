#include "MatrixSimulationSystemCommandLine.h"
#include "Engine/World.h"

#include "Misc/Guid.h"
#include "TimerManager.h"

AMatrixSimulationSystemCommandLine::AMatrixSimulationSystemCommandLine()
{
    PrimaryActorTick.bCanEverTick = false; // we use timers instead
}

void AMatrixSimulationSystemCommandLine::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("Matrix Simulation System Command Line Initialized."));

    // Initialize frequency layers
    AddFrequencyLayer(50.f);
    AddFrequencyLayer(60.f);
    AddFrequencyLayer(70.f);

    // Automate command addition and execution (InvokeRepeating equivalent)
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(AutoGenHandle, this, &AMatrixSimulationSystemCommandLine::AutoGenerateCommands, AutoGenerateInterval, true, AutoGenerateInitialDelay);
        World->GetTimerManager().SetTimer(ExecHandle, this, &AMatrixSimulationSystemCommandLine::ExecuteNextCommand, ExecuteInterval, true, ExecuteInitialDelay);
    }
}

// ===== FCommand =====
AMatrixSimulationSystemCommandLine::FCommand::FCommand(const FString& InDescription, const FString& InSource)
    : CommandID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
    , Description(InDescription)
    , Source(InSource)
{
}

void AMatrixSimulationSystemCommandLine::FCommand::MarkSecure()
{
    bIsSecure = true;
    UE_LOG(LogTemp, Log, TEXT("Command '%s' marked as secure."), *CommandID);
}

// ===== FOctaRecreationalFeed =====
AMatrixSimulationSystemCommandLine::FOctaRecreationalFeed::FOctaRecreationalFeed()
    : FeedID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
{
}

void AMatrixSimulationSystemCommandLine::FOctaRecreationalFeed::AddFrequencyLayer(float Frequency)
{
    FrequencyLayers.Add(Frequency);
    UE_LOG(LogTemp, Log, TEXT("Frequency Layer Added - FeedID: %s, Frequency: %.2f Hz"), *FeedID, Frequency);
}

float AMatrixSimulationSystemCommandLine::FOctaRecreationalFeed::GenerateFieldWave() const
{
    if (FrequencyLayers.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No frequency layers in feed to generate field wave."));
        return 0.f;
    }

    float Combined = 0.f;
    for (float F : FrequencyLayers)
    {
        Combined += F;
    }
    const float FieldWave = Combined / static_cast<float>(FrequencyLayers.Num());
    UE_LOG(LogTemp, Log, TEXT("Generated Field Wave: %.2f Hz"), FieldWave);
    return FieldWave;
}

// ===== Public API =====
void AMatrixSimulationSystemCommandLine::AddCommand(const FString& Description, const FString& Source)
{
    FCommand Cmd(Description, Source);
    CommandQueue.Add(Cmd);
    UE_LOG(LogTemp, Log, TEXT("Command Added - ID: %s, Description: %s, Source: %s"), *Cmd.CommandID, *Description, *Source);
}

void AMatrixSimulationSystemCommandLine::AddFrequencyLayer(float Frequency)
{
    OctaFeed.AddFrequencyLayer(Frequency);
}

bool AMatrixSimulationSystemCommandLine::AnalyzeCommand(FCommand& Command)
{
    UE_LOG(LogTemp, Log, TEXT("Analyzing command - Source: %s, Description: %s"), *Command.Source, *Command.Description);
    if (Command.Source.StartsWith(TEXT("Authorized")))
    {
        Command.MarkSecure();
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Unauthorized command detected: %s"), *Command.Description);
        ContainUnauthorizedData(Command);
        return false;
    }
}

void AMatrixSimulationSystemCommandLine::ContainUnauthorizedData(const FCommand& Command)
{
    UE_LOG(LogTemp, Warning, TEXT("Containment initiated for unauthorized command - ID: %s"), *Command.CommandID);
    // Simulate security measures
}

void AMatrixSimulationSystemCommandLine::ProcessCommand(const FCommand& Command)
{
    if (Command.bIsSecure)
    {
        UE_LOG(LogTemp, Log, TEXT("Processing secure command - ID: %s, Description: %s"), *Command.CommandID, *Command.Description);
        const float FieldWave = OctaFeed.GenerateFieldWave();
        UE_LOG(LogTemp, Log, TEXT("Command processed with field wave: %.2f Hz"), FieldWave);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Command '%s' is not secure and cannot be processed."), *Command.CommandID);
    }
}

void AMatrixSimulationSystemCommandLine::ExecuteNextCommand()
{
    if (CommandQueue.Num() > 0)
    {
        FCommand Command = CommandQueue[0];
        CommandQueue.RemoveAt(0);

        if (AnalyzeCommand(Command))
        {
            ProcessCommand(Command);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No commands in the queue to execute."));
    }
}

void AMatrixSimulationSystemCommandLine::AutoGenerateCommands()
{
    if (FMath::FRand() > 0.5f)
    {
        AddCommand(TEXT("Simulate Frequency Hallucination"), TEXT("AuthorizedUser"));
    }
    else
    {
        AddCommand(TEXT("Access Secure Data"), TEXT("UnauthorizedSource"));
    }

    // Add random frequency layer
    AddFrequencyLayer(FMath::FRandRange(40.f, 100.f));
}

