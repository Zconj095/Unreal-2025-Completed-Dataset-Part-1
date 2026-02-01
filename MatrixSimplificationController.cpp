#include "MatrixSimplificationController.h"

#include "Misc/Guid.h"

AMatrixSimplificationController::AMatrixSimplificationController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixSimplificationController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Simplification Controller Initialized."));
}

void AMatrixSimplificationController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timers
    AddTaskTimer += DeltaSeconds;
    ProcessTaskTimer += DeltaSeconds;
    AdjustOptionsTimer += DeltaSeconds;

    // Automate task addition
    if (AddTaskTimer >= AddTaskInterval)
    {
        const float Raw = FMath::FRandRange(1.0f, 100.0f);
        AddTask(TEXT("Auto-Generated Task"), Raw);
        AddTaskTimer = 0.f;
    }

    // Automate task processing
    if (ProcessTaskTimer >= ProcessTaskInterval)
    {
        ProcessNextTask();
        ProcessTaskTimer = 0.f;
    }

    // Automate adjustment of simulation options
    if (AdjustOptionsTimer >= AdjustOptionsInterval)
    {
        AdjustSimulationOptions();
        AdjustOptionsTimer = 0.f;
    }
}

void AMatrixSimplificationController::AddTask(const FString& Description, float RawValue)
{
    FSimulationTask Task(Description, RawValue);
    UE_LOG(LogTemp, Log, TEXT("Task Added - ID: %s, Description: %s, Raw Value: %.2f, Simplified: %.0f%%"), *Task.TaskID, *Description, RawValue, Task.Percentage);
    TaskQueue.Enqueue(MoveTemp(Task));
    ++PendingTaskCount;
}

void AMatrixSimplificationController::ProcessNextTask()
{
    if (PendingTaskCount > 0 && !TaskQueue.IsEmpty())
    {
        FSimulationTask Task;
        const bool bDequeued = TaskQueue.Dequeue(Task);
        if (bDequeued)
        {
            --PendingTaskCount;
            Task.MarkProcessed();
            ProcessedTasks.Add(Task);
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No tasks in the queue to process."));
    }
}

void AMatrixSimplificationController::AdjustSimulationOptions() const
{
    UE_LOG(LogTemp, Log, TEXT("Adjusting simulation options based on processed tasks..."));
    for (const FSimulationTask& Task : ProcessedTasks)
    {
        UE_LOG(LogTemp, Log, TEXT("Processed Task - ID: %s, Adjustment Percentage: %.0f%%"), *Task.TaskID, Task.Percentage);
    }
}

void AMatrixSimplificationController::DisplayTaskStatus() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying task statuses..."));
    for (const FSimulationTask& Task : ProcessedTasks)
    {
        UE_LOG(LogTemp, Log, TEXT("Task - ID: %s, Description: %s, Percentage: %.0f%%, Processed: %s"), *Task.TaskID, *Task.Description, Task.Percentage, Task.bIsProcessed ? TEXT("true") : TEXT("false"));
    }

    if (PendingTaskCount > 0)
    {
        UE_LOG(LogTemp, Log, TEXT("Pending Tasks: %d"), PendingTaskCount);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("No pending tasks."));
    }
}

