// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationDriverSystem.generated.h"

USTRUCT(BlueprintType)
struct FDriver
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Driver")
    FString DriverID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Driver")
    FString Name;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Driver")
    float CommandStrength = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Driver")
    bool bIsSynchronized = false;

    FDriver() {}
    FDriver(const FString& InName, float BaseStrength)
        : DriverID(FGuid::NewGuid().ToString())
        , Name(InName)
        , CommandStrength(BaseStrength * 2.0f)
        , bIsSynchronized(false)
    {}

    void Synchronize()
    {
        bIsSynchronized = true;
        UE_LOG(LogTemp, Log, TEXT("Driver '%s' synchronized successfully."), *Name);
    }

    void ExecuteTask(const FString& Task) const
    {
        if (!bIsSynchronized)
        {
            UE_LOG(LogTemp, Warning, TEXT("Driver '%s' is not synchronized. Task execution may be suboptimal."), *Name);
        }
        UE_LOG(LogTemp, Log, TEXT("Driver '%s' executing task: %s with strength: %.2f"), *Name, *Task, CommandStrength);
    }

    void Display() const
    {
        UE_LOG(LogTemp, Log, TEXT("Driver ID: %s, Name: %s, Strength: %.2f, Synchronized: %s"), *DriverID, *Name, CommandStrength, bIsSynchronized ? TEXT("true") : TEXT("false"));
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationDriverSystem : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationDriverSystem();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|DriverSystem")
    void CreateDriver(const FString& Name, float BaseStrength);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|DriverSystem")
    void SynchronizeDrivers();

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|DriverSystem")
    void ExecuteTaskAcrossDrivers(const FString& Task);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|DriverSystem")
    void DisplayDrivers() const;

private:
    // Data
    UPROPERTY()
    TArray<FDriver> Drivers;

    // Timers
    FTimerHandle TimerHandle_AutoCreate;
    FTimerHandle TimerHandle_AutoSync;
    FTimerHandle TimerHandle_AutoExecute;
    FTimerHandle TimerHandle_Display;

    // Auto helpers
    void AutoCreateDriver();
    void AutoSynchronizeDrivers();
    void AutoExecuteTasks();
};

