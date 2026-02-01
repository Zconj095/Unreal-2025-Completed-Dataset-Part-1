// Converted from Unity MonoBehaviour QuantumCortex to Unreal ActorComponent.
#include "QuantumCortexComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

UQuantumCortexComponent::UQuantumCortexComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuantumCortexComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeDataset();
    EnqueueDefaultTasks();
    ProcessCognitiveThreads();
}

void UQuantumCortexComponent::InitializeDataset()
{
    QuantumDataset.Reset();
    QuantumDataset.Reserve(DatasetSize);
    for (int32 Index = 0; Index < DatasetSize; ++Index)
    {
        QuantumDataset.Add(FMath::RandRange(0, 99));
    }
}

void UQuantumCortexComponent::EnqueueDefaultTasks()
{
    TaskQueue.Reset();

    FQuantumCortexQueuedTask Task1;
    Task1.TaskName = TEXT("Task 1");
    Task1.TaskDelegate.BindUObject(this, &UQuantumCortexComponent::PatternAnalysis);
    TaskQueue.Add(Task1);

    FQuantumCortexQueuedTask Task2;
    Task2.TaskName = TEXT("Task 2");
    Task2.TaskDelegate.BindUObject(this, &UQuantumCortexComponent::PatternAnalysis);
    TaskQueue.Add(Task2);

    FQuantumCortexQueuedTask GroverTask;
    GroverTask.TaskName = TEXT("Grover Optimization");
    GroverTask.TaskDelegate.BindLambda([this](const FString&)
    {
        GroverOptimization();
    });
    TaskQueue.Add(GroverTask);

    FQuantumCortexQueuedTask GeneralTask;
    GeneralTask.TaskName = TEXT("Final Task");
    GeneralTask.TaskDelegate.BindUObject(this, &UQuantumCortexComponent::GeneralTaskSimulation);
    TaskQueue.Add(GeneralTask);
}

void UQuantumCortexComponent::ProcessCognitiveThreads()
{
    if (TaskQueue.Num() == 0 && RunningTasks == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("All tasks completed."));
        return;
    }

    while (RunningTasks < NumberOfThreads && TaskQueue.Num() > 0)
    {
        const FQuantumCortexQueuedTask Task = TaskQueue[0];
        TaskQueue.RemoveAt(0);
        StartTask(Task);
    }
}

void UQuantumCortexComponent::StartTask(const FQuantumCortexQueuedTask& Task)
{
    ++RunningTasks;

    const float Delay = FMath::FRandRange(0.1f, 0.5f);
    FTimerHandle LocalHandle;
    if (GetWorld())
    {
            GetWorld()->GetTimerManager().SetTimer(
                LocalHandle,
            FTimerDelegate::CreateLambda([this, Task]()
            {
                Task.TaskDelegate.ExecuteIfBound(Task.TaskName);
                TaskCompleted();
            }),
            Delay,
            false);
    }
}

void UQuantumCortexComponent::TaskCompleted()
{
    --RunningTasks;
    ProcessCognitiveThreads();
}

void UQuantumCortexComponent::PatternAnalysis(const FString& TaskName)
{
    UE_LOG(LogTemp, Log, TEXT("%s: Performing pattern analysis..."), *TaskName);
    if (QuantumDataset.Num() == 0)
    {
        return;
    }

    int32 MaxValue = QuantumDataset[0];
    for (int32 Value : QuantumDataset)
    {
        MaxValue = FMath::Max(MaxValue, Value);
    }

    UE_LOG(LogTemp, Log, TEXT("%s: Analysis complete. Max value in dataset: %d"), *TaskName, MaxValue);
}

void UQuantumCortexComponent::GroverOptimization()
{
    UE_LOG(LogTemp, Log, TEXT("Starting Grover's Optimization..."));
    int32 BestGuess = -1;

    for (int32 Value : QuantumDataset)
    {
        if (Value == OptimalValue)
        {
            BestGuess = Value;
            break;
        }
    }

    if (BestGuess != -1)
    {
        UE_LOG(LogTemp, Log, TEXT("Optimization successful! Found optimal value: %d"), BestGuess);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Optimization failed. Target not found."));
    }
}

void UQuantumCortexComponent::GeneralTaskSimulation(const FString& TaskName)
{
    UE_LOG(LogTemp, Log, TEXT("%s: Executing general computational task..."), *TaskName);
}
