#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationSystemCommandLine.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationSystemCommandLine : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationSystemCommandLine();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Matrix CLI")
    void AddCommand(const FString& Description, const FString& Source);

    UFUNCTION(BlueprintCallable, Category = "Matrix CLI")
    void AddFrequencyLayer(float Frequency);

protected:
    // Timers emulate Unity's InvokeRepeating
    UPROPERTY(EditAnywhere, Category = "Automation")
    float AutoGenerateInitialDelay = 1.f;

    UPROPERTY(EditAnywhere, Category = "Automation")
    float AutoGenerateInterval = 5.f;

    UPROPERTY(EditAnywhere, Category = "Automation")
    float ExecuteInitialDelay = 3.f;

    UPROPERTY(EditAnywhere, Category = "Automation")
    float ExecuteInterval = 7.f;

private:
    struct FCommand
    {
        FString CommandID;
        FString Description;
        FString Source;
        bool bIsSecure = false;

        FCommand() = default;
        FCommand(const FString& InDescription, const FString& InSource);

        void MarkSecure();
    };

    class FOctaRecreationalFeed
    {
    public:
        FOctaRecreationalFeed();

        void AddFrequencyLayer(float Frequency);
        float GenerateFieldWave() const; // average of layers

    private:
        FString FeedID;
        TArray<float> FrequencyLayers;
    };

    bool AnalyzeCommand(FCommand& Command);
    void ContainUnauthorizedData(const FCommand& Command);
    void ProcessCommand(const FCommand& Command);

    UFUNCTION()
    void ExecuteNextCommand();

    UFUNCTION()
    void AutoGenerateCommands();

    // Data
    TArray<FCommand> CommandQueue;
    FOctaRecreationalFeed OctaFeed;

    // Timers
    FTimerHandle AutoGenHandle;
    FTimerHandle ExecHandle;
};

