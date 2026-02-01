// Converted from Unity MonoBehaviour AdaptiveQuantumCortex to Unreal ActorComponent.
#include "AdaptiveQuantumCortexComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"

UAdaptiveQuantumCortexComponent::UAdaptiveQuantumCortexComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UAdaptiveQuantumCortexComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeDataset();
    ScheduleTasks();
    StartProcessing();
}

void UAdaptiveQuantumCortexComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    ReflectiveUpdates();
}

void UAdaptiveQuantumCortexComponent::InitializeDataset()
{
    QuantumDataset.Reset();
    QuantumDataset.Reserve(DatasetSize);

    for (int32 Index = 0; Index < DatasetSize; ++Index)
    {
        QuantumDataset.Add(FMath::RandRange(0, 99));
    }

    UE_LOG(LogTemp, Log, TEXT("Dataset initialized (%d entries)."), QuantumDataset.Num());
}

void UAdaptiveQuantumCortexComponent::ScheduleTasks()
{
    AddTask(TEXT("Pattern Analysis Task"), [this]() { PatternAnalysis(TEXT("Pattern Analysis Task")); });
    AddTask(TEXT("Grover Optimization Task"), [this]() { GroverOptimization(TEXT("Grover Optimization Task")); });
    AddTask(TEXT("Adaptive Task Simulation"), [this]() { AdaptiveTask(TEXT("Adaptive Task Simulation")); });
}

void UAdaptiveQuantumCortexComponent::AddTask(const FString& TaskName, TFunction<void()> Task)
{
    TaskQueue.Add({TaskName, MoveTemp(Task)});
    TaskStatuses.Add(TaskName, TEXT("Scheduled"));
}

void UAdaptiveQuantumCortexComponent::StartProcessing()
{
    if (!bIsProcessing)
    {
        bIsProcessing = true;
        ProcessNextBatch();
    }
}

void UAdaptiveQuantumCortexComponent::ProcessNextBatch()
{
    if (TaskQueue.Num() == 0 && ActiveTasks == 0)
    {
        bIsProcessing = false;
        UE_LOG(LogTemp, Log, TEXT("All tasks completed."));
        return;
    }

    while (ActiveTasks < NumberOfThreads && TaskQueue.Num() > 0)
    {
        FAdaptiveTaskEntry TaskEntry = TaskQueue[0];
        TaskQueue.RemoveAt(0);

        TaskStatuses.Add(TaskEntry.TaskName, TEXT("In Progress"));
        TaskRunner(MoveTemp(TaskEntry));
    }
}

void UAdaptiveQuantumCortexComponent::TaskRunner(FAdaptiveTaskEntry TaskEntry)
{
    ++ActiveTasks;

    const float Delay = FMath::FRandRange(0.1f, TaskUpdateInterval);
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        FTimerDelegate::CreateLambda([this, TaskEntry = MoveTemp(TaskEntry)]()
        {
            TaskEntry.TaskFunc();
            TaskStatuses.Add(TaskEntry.TaskName, TEXT("Completed"));
            --ActiveTasks;
            ProcessNextBatch();
        }),
        Delay,
        false);
}

void UAdaptiveQuantumCortexComponent::ReflectiveUpdates()
{
    UE_LOG(LogTemp, Verbose, TEXT("Dataset Size: %d | Target Value: %d"), DatasetSize, TargetValue);

    for (const auto& Pair : TaskStatuses)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Task: %s | Status: %s"), *Pair.Key, *Pair.Value);
    }
}

void UAdaptiveQuantumCortexComponent::PatternAnalysis(const FString& TaskName)
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

    UE_LOG(LogTemp, Log, TEXT("%s: Max value in dataset: %d"), *TaskName, MaxValue);
}

void UAdaptiveQuantumCortexComponent::GroverOptimization(const FString& TaskName)
{
    UE_LOG(LogTemp, Log, TEXT("%s: Starting optimization..."), *TaskName);

    const int32 BestGuess = QuantumDataset.Contains(TargetValue) ? TargetValue : -1;
    if (BestGuess != -1)
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Optimization successful! Found value: %d"), *TaskName, BestGuess);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("%s: Optimization failed."), *TaskName);
    }
}

void UAdaptiveQuantumCortexComponent::AdaptiveTask(const FString& TaskName)
{
    UE_LOG(LogTemp, Log, TEXT("%s: Simulating dynamic behavior..."), *TaskName);

    if (NumberOfThreads < 8)
    {
        ++NumberOfThreads;
        UE_LOG(LogTemp, Log, TEXT("%s: Increased thread count to %d"), *TaskName, NumberOfThreads);
    }
    else
    {
        NumberOfThreads = 4;
        UE_LOG(LogTemp, Log, TEXT("%s: Reset thread count to %d"), *TaskName, NumberOfThreads);
    }
}
