// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationCommandLine.generated.h"

USTRUCT(BlueprintType)
struct FCommandEntry
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Command")
    FString CommandID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Command")
    FString Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Command")
    FString Category;

    FCommandEntry() {}
    FCommandEntry(const FString& InContent, const FString& InCategory)
        : CommandID(FGuid::NewGuid().ToString())
        , Content(InContent)
        , Category(InCategory)
    {}

    void Display() const
    {
        UE_LOG(LogTemp, Log, TEXT("Command ID: %s, Content: %s, Category: %s"), *CommandID, *Content, *Category);
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationCommandLine : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationCommandLine();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|CommandLine")
    void AddCommand(const FString& Content, const FString& Category);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|CommandLine")
    void DisplayCommands() const;

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|CommandLine")
    void ReplenishEnergy(float Amount);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|CommandLine")
    void ExecuteCommand(const FString& CommandID);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|CommandLine")
    void ResetEnergy();

private:
    // Data
    UPROPERTY()
    TArray<FCommandEntry> CommandDictionary;

    UPROPERTY(EditAnywhere, Category = "SystemAdmin|CommandLine")
    float SharedEnergy = 10000.f;

    // Timers
    FTimerHandle TimerHandle_AutoAdd;
    FTimerHandle TimerHandle_AutoExecute;
    FTimerHandle TimerHandle_AutoReplenish;
    FTimerHandle TimerHandle_Display;

    // Auto helpers
    void AutoAddCommand();
    void AutoExecuteCommand();
    void AutoReplenishEnergy();
};

