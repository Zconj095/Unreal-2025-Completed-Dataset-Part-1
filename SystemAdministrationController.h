// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationController.generated.h"

USTRUCT(BlueprintType)
struct FAdminTask
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Task")
    FString TaskID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Task")
    FString Description;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Task")
    bool bIsCompleted = false;

    FAdminTask() {}
    FAdminTask(const FString& InDescription)
        : TaskID(FGuid::NewGuid().ToString())
        , Description(InDescription)
        , bIsCompleted(false)
    {}
};

USTRUCT(BlueprintType)
struct FAdminOption
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Option")
    FString OptionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Option")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Option")
    FString Modifier;

    FAdminOption() {}
    FAdminOption(const FString& InName, const FString& InModifier)
        : OptionID(FGuid::NewGuid().ToString())
        , Name(InName)
        , Modifier(InModifier)
    {}
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationController : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationController();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Controller")
    void AddTask(const FString& Description);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Controller")
    void CompleteTask(const FString& TaskID);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Controller")
    void AddOption(const FString& Name, const FString& Modifier);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Controller")
    void ApplyOption(const FString& OptionID);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Controller")
    void DisplayTasks() const;

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Controller")
    void DisplayOptions() const;

private:
    // Data
    UPROPERTY()
    TArray<FAdminTask> Tasks;

    UPROPERTY()
    TArray<FAdminOption> Options;

    // Timers
    FTimerHandle TimerHandle_AutoAddTask;
    FTimerHandle TimerHandle_AutoCompleteTask;
    FTimerHandle TimerHandle_AutoAddOption;
    FTimerHandle TimerHandle_AutoApplyOption;
    FTimerHandle TimerHandle_DisplayTasks;
    FTimerHandle TimerHandle_DisplayOptions;

    // Auto helpers
    void AutoAddTask();
    void AutoCompleteTask();
    void AutoAddOption();
    void AutoApplyOption();
};

