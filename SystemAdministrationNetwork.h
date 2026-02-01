// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationNetwork.generated.h"

USTRUCT(BlueprintType)
struct FNetworkEntry
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Network")
    FString NetworkID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Network")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Network")
    FString Type; // Public, Private, Server, etc.

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Network")
    bool bIsActive = false;

    FNetworkEntry() {}
    FNetworkEntry(const FString& InName, const FString& InType, bool bInActive)
        : NetworkID(FGuid::NewGuid().ToString())
        , Name(InName)
        , Type(InType)
        , bIsActive(bInActive)
    {}

    void Activate()
    {
        bIsActive = true;
        UE_LOG(LogTemp, Log, TEXT("Network '%s' activated."), *Name);
    }

    void Deactivate()
    {
        bIsActive = false;
        UE_LOG(LogTemp, Log, TEXT("Network '%s' deactivated."), *Name);
    }

    void Display() const
    {
        UE_LOG(LogTemp, Log, TEXT("Network ID: %s, Name: %s, Type: %s, Active: %s"), *NetworkID, *Name, *Type, bIsActive ? TEXT("true") : TEXT("false"));
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationNetwork : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationNetwork();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Network")
    void AddNetwork(const FString& Name, const FString& Type, bool bIsActive = false);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Network")
    void ToggleNetwork(const FString& NetworkID, bool bActivate);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Network")
    void DisplayNetworks() const;

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Network")
    void ToggleInfinityMatrix(bool bActivate);

private:
    // Data
    UPROPERTY()
    TArray<FNetworkEntry> Networks;

    UPROPERTY(VisibleAnywhere, Category = "SystemAdmin|Network")
    bool bInfinityMatrixActive = true;

    // Timers
    FTimerHandle TimerHandle_AutoAdd;
    FTimerHandle TimerHandle_AutoToggleNetwork;
    FTimerHandle TimerHandle_AutoDisplay;
    FTimerHandle TimerHandle_AutoToggleInfinityMatrix;

    // Auto helpers
    void AutoAddNetwork();
    void AutoToggleNetwork();
    void AutoDisplayNetworks();
    void AutoToggleInfinityMatrix();
};

