#include "MatrixManagementSystem.h"
#include "Engine/World.h"

#include "Containers/Queue.h"

AMatrixManagementSystem::AMatrixManagementSystem()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixManagementSystem::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Management System Initialized."));
}

void AMatrixManagementSystem::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timers
    AddCommandTimer += DeltaSeconds;
    ExecuteCommandTimer += DeltaSeconds;
    RetrieveStatusTimer += DeltaSeconds;
    RetrieveKnowledgeTimer += DeltaSeconds;

    // Automate adding commands
    if (AddCommandTimer >= AddCommandInterval)
    {
        const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
        AddCommand(FString::Printf(TEXT("Automated Command %.2f"), TimeSeconds));
        AddCommandTimer = 0.f;
    }

    // Automate executing commands
    if (ExecuteCommandTimer >= ExecuteCommandInterval)
    {
        ExecuteNextCommand();
        ExecuteCommandTimer = 0.f;
    }

    // Automate retrieving command statuses
    if (RetrieveStatusTimer >= RetrieveStatusInterval)
    {
        RetrieveCommandStatus();
        RetrieveStatusTimer = 0.f;
    }

    // Automate retrieving the knowledge database
    if (RetrieveKnowledgeTimer >= RetrieveKnowledgeInterval)
    {
        RetrieveKnowledgeDatabase();
        RetrieveKnowledgeTimer = 0.f;
    }
}

void AMatrixManagementSystem::AddCommand(const FString& CommandText)
{
    FMatrixCommand Command(CommandText);
    UE_LOG(LogTemp, Log, TEXT("Command Added - ID: %s, Text: %s"), *Command.CommandID, *CommandText);
    CommandQueue.Enqueue(MoveTemp(Command));
}

void AMatrixManagementSystem::ExecuteNextCommand()
{
    if (!CommandQueue.IsEmpty())
    {
        FMatrixCommand Command(TEXT(""));
        const bool bDequeued = CommandQueue.Dequeue(Command);
        if (bDequeued)
        {
            Command.Execute();
            CompletedCommands.Add(Command); // stored copy of completed command
            LearnFromCommand(Command.CommandText);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No commands in the queue to execute."));
    }
}

void AMatrixManagementSystem::LearnFromCommand(const FString& CommandText)
{
    int32& Count = KnowledgeDatabase.FindOrAdd(CommandText, 0);
    Count++;
    if (Count > 1)
    {
        UE_LOG(LogTemp, Log, TEXT("Knowledge increased for command: %s, Count: %d"), *CommandText, Count);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("New knowledge entry added for command: %s"), *CommandText);
    }
}

void AMatrixManagementSystem::RetrieveCommandStatus() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving command statuses..."));
    for (const FMatrixCommand& Command : CompletedCommands)
    {
        UE_LOG(LogTemp, Log, TEXT("Command - ID: %s, Text: %s, Status: %s"), *Command.CommandID, *Command.CommandText, *Command.Status);
    }
}

void AMatrixManagementSystem::RetrieveKnowledgeDatabase() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving knowledge database..."));
    for (const TPair<FString, int32>& Pair : KnowledgeDatabase)
    {
        UE_LOG(LogTemp, Log, TEXT("Knowledge Entry - Command: %s, Usage Count: %d"), *Pair.Key, Pair.Value);
    }
}

