// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationInterface.generated.h"

USTRUCT(BlueprintType)
struct FVirtualConnection
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Interface")
    FString ConnectionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Interface")
    FString InputAxis;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Interface")
    FString OutputAxis;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Interface")
    float Frequency = 0.f; // Hz

    FVirtualConnection() {}
    FVirtualConnection(const FString& InInput, const FString& InOutput, float InFrequency)
        : ConnectionID(FGuid::NewGuid().ToString())
        , InputAxis(InInput)
        , OutputAxis(InOutput)
        , Frequency(InFrequency)
    {}

    void AnalyzeConnection() const
    {
        UE_LOG(LogTemp, Log, TEXT("Analyzing Connection '%s'..."), *ConnectionID);
        UE_LOG(LogTemp, Log, TEXT("Input Axis: %s, Output Axis: %s, Frequency: %.2f Hz"), *InputAxis, *OutputAxis, Frequency);
    }

    void BounceBack() const
    {
        UE_LOG(LogTemp, Log, TEXT("Bouncing back frequency %.2f Hz from Output Axis '%s' to Input Axis '%s'..."), Frequency, *OutputAxis, *InputAxis);
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationInterface : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationInterface();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Interface")
    void CreateVirtualConnection(const FString& InputAxis, const FString& OutputAxis, float Frequency);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Interface")
    void AnalyzeAllConnections() const;

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Interface")
    void ExecuteBounceBack() const;

private:
    // Data
    UPROPERTY()
    TArray<FVirtualConnection> VirtualConnections;

    // Timers
    FTimerHandle TimerHandle_AutoAdd;
    FTimerHandle TimerHandle_AutoAnalyze;
    FTimerHandle TimerHandle_AutoBounce;

    // Auto helpers
    void AutoAddConnection();
    void AutoAnalyzeConnections();
    void AutoBounceBack();
};

