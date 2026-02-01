#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimplificationController.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimplificationController : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimplificationController();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simplification")
    void AddTask(const FString& Description, float RawValue);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simplification")
    void ProcessNextTask();

    UFUNCTION(BlueprintCallable, Category = "Matrix Simplification")
    void AdjustSimulationOptions() const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simplification")
    void DisplayTaskStatus() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float AddTaskInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float ProcessTaskInterval = 3.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float AdjustOptionsInterval = 10.f; // seconds

private:
    struct FSimulationTask
    {
        FString TaskID;
        FString Description;
        float Percentage = 0.f; // Rounded to nearest percent
        bool bIsProcessed = false;

        FSimulationTask() = default;
        FSimulationTask(const FString& InDescription, float RawValue)
            : TaskID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , Description(InDescription)
        {
            // Round to nearest integer percentage, matching Unity Mathf.Round behavior
            const int32 Rounded = FMath::RoundHalfFromZero(RawValue);
            Percentage = static_cast<float>(Rounded);
        }

        void MarkProcessed()
        {
            bIsProcessed = true;
            UE_LOG(LogTemp, Log, TEXT("Task '%s' processed: %s => %.0f%%"), *TaskID, *Description, Percentage);
        }
    };

    // Data
    TQueue<FSimulationTask> TaskQueue;
    TArray<FSimulationTask> ProcessedTasks;
    int32 PendingTaskCount = 0; // Track size of TaskQueue

    // Timers
    float AddTaskTimer = 0.f;
    float ProcessTaskTimer = 0.f;
    float AdjustOptionsTimer = 0.f;
};

