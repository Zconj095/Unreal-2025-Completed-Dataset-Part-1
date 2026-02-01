#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationEditor.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationEditor : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationEditor();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Editor")
    void AddSetting(const FString& Name, float InitialValue);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Editor")
    void UpdateSetting(const FString& Name, float NewValue);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Editor")
    void ExecuteCommand(const FString& CommandText);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Editor")
    void RevertCommand(const FString& CommandID);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Editor")
    void DisplaySettings() const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Editor")
    void DisplayCommands() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float TaskInterval = 3.f; // seconds

private:
    struct FEditorSetting
    {
        FString Name;
        float Value = 0.f;

        FEditorSetting() = default;
        FEditorSetting(const FString& InName, float InitialValue)
            : Name(InName)
            , Value(InitialValue)
        {
        }

        void UpdateValue(float NewValue)
        {
            Value = FMath::Clamp(NewValue, 0.f, 100.f);
            UE_LOG(LogTemp, Log, TEXT("Setting '%s' updated to: %.2f"), *Name, Value);
        }
    };

    struct FEditorCommand
    {
        FString CommandID;
        FString CommandText;

        FEditorCommand() = default;
        explicit FEditorCommand(const FString& InText)
            : CommandID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , CommandText(InText)
        {
        }
    };

    void TransferPowerToEditor(const FString& CommandText) const;
    float CalculatePower(const FString& CommandText) const;
    void PerformAutomatedTasks();

    // Settings and commands
    TMap<FString, FEditorSetting> Settings; // Name -> Setting
    TArray<FEditorCommand> Commands;

    // Timer
    float TaskTimer = 0.f;
};

