#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixManagementSystem.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixManagementSystem : public AActor
{
    GENERATED_BODY()

public:
    AMatrixManagementSystem();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Management")
    void AddCommand(const FString& CommandText);

    UFUNCTION(BlueprintCallable, Category = "Matrix Management")
    void ExecuteNextCommand();

    UFUNCTION(BlueprintCallable, Category = "Matrix Management")
    void RetrieveCommandStatus() const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Management")
    void RetrieveKnowledgeDatabase() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float AddCommandInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float ExecuteCommandInterval = 3.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float RetrieveStatusInterval = 10.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float RetrieveKnowledgeInterval = 15.f; // seconds

private:
    struct FMatrixCommand
    {
        FString CommandID;
        FString CommandText;
        FString Status; // Pending / Completed

        FMatrixCommand() = default;
        explicit FMatrixCommand(const FString& InText)
            : CommandID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , CommandText(InText)
            , Status(TEXT("Pending"))
        {
        }

        void Execute()
        {
            Status = TEXT("Completed");
            UE_LOG(LogTemp, Log, TEXT("Command '%s' executed: %s"), *CommandID, *CommandText);
        }
    };

    void LearnFromCommand(const FString& CommandText);

    // Data
    TQueue<FMatrixCommand> CommandQueue;
    TArray<FMatrixCommand> CompletedCommands;
    TMap<FString, int32> KnowledgeDatabase; // CommandText -> Count

    // Timers
    float AddCommandTimer = 0.f;
    float ExecuteCommandTimer = 0.f;
    float RetrieveStatusTimer = 0.f;
    float RetrieveKnowledgeTimer = 0.f;
};
