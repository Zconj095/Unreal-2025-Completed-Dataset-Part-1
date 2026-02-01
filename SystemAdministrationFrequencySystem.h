// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationFrequencySystem.generated.h"

USTRUCT(BlueprintType)
struct FFrequencyChannel
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Frequency")
    FString ChannelID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Frequency")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Frequency")
    float Frequency = 0.f; // Hz

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Frequency")
    FString Purpose;

    FFrequencyChannel() {}
    FFrequencyChannel(const FString& InName, float InFrequency, const FString& InPurpose)
        : ChannelID(FGuid::NewGuid().ToString())
        , Name(InName)
        , Frequency(InFrequency)
        , Purpose(InPurpose)
    {}

    void UpdateFrequency(float NewFrequency)
    {
        Frequency = NewFrequency;
        UE_LOG(LogTemp, Log, TEXT("Frequency Channel '%s' updated to %.2f Hz."), *Name, Frequency);
    }

    void Display() const
    {
        UE_LOG(LogTemp, Log, TEXT("Channel ID: %s, Name: %s, Frequency: %.2f Hz, Purpose: %s"), *ChannelID, *Name, Frequency, *Purpose);
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationFrequencySystem : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationFrequencySystem();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Frequency")
    void AddFrequencyChannel(const FString& Name, float Frequency, const FString& Purpose);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Frequency")
    void EditFrequencyChannel(const FString& ChannelID, float NewFrequency);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Frequency")
    void DisplayFrequencyChannels() const;

private:
    // Data
    UPROPERTY()
    TArray<FFrequencyChannel> FrequencyChannels;

    // Timers
    FTimerHandle TimerHandle_AutoAdd;
    FTimerHandle TimerHandle_AutoEdit;
    FTimerHandle TimerHandle_AutoDisplay;

    // Auto helpers
    void AutoAddFrequencyChannel();
    void AutoEditFrequencyChannel();
    void AutoDisplayFrequencyChannels();
};

