// Converted from Unity C# to Unreal C++
#include "SystemAdministrationNetwork.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationNetwork::ASystemAdministrationNetwork()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationNetwork::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("Automated System Administration Network Initialized."));

    // Initial setup
    AddNetwork(TEXT("Public Network"), TEXT("Public"), true);
    AddNetwork(TEXT("Private Network"), TEXT("Private"), false);
    AddNetwork(TEXT("Server Network"), TEXT("Server"), false);

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Add a new network every 15 seconds (delay 3s)
        TM.SetTimer(
            TimerHandle_AutoAdd,
            this,
            &ASystemAdministrationNetwork::AutoAddNetwork,
            15.0f,
            true,
            3.0f);

        // Toggle a random network every 10 seconds (delay 5s)
        TM.SetTimer(
            TimerHandle_AutoToggleNetwork,
            this,
            &ASystemAdministrationNetwork::AutoToggleNetwork,
            10.0f,
            true,
            5.0f);

        // Display networks every 20 seconds (delay 10s)
        TM.SetTimer(
            TimerHandle_AutoDisplay,
            this,
            &ASystemAdministrationNetwork::AutoDisplayNetworks,
            20.0f,
            true,
            10.0f);

        // Toggle Infinity Matrix power every 60 seconds (delay 30s)
        TM.SetTimer(
            TimerHandle_AutoToggleInfinityMatrix,
            this,
            &ASystemAdministrationNetwork::AutoToggleInfinityMatrix,
            60.0f,
            true,
            30.0f);
    }
}

void ASystemAdministrationNetwork::AddNetwork(const FString& Name, const FString& Type, bool bIsActive)
{
    FNetworkEntry NewNetwork(Name, Type, bIsActive);
    Networks.Add(NewNetwork);
    UE_LOG(LogTemp, Log, TEXT("New Network Added - ID: %s, Name: %s, Type: %s, Active: %s"), *NewNetwork.NetworkID, *Name, *Type, bIsActive ? TEXT("true") : TEXT("false"));
}

void ASystemAdministrationNetwork::ToggleNetwork(const FString& NetworkID, bool bActivate)
{
    if (!bInfinityMatrixActive && bActivate)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot activate networks while the Infinity Matrix is inactive."));
        return;
    }

    const int32 Index = Networks.IndexOfByPredicate([&](const FNetworkEntry& N){ return N.NetworkID == NetworkID; });
    if (Index != INDEX_NONE)
    {
        if (bActivate)
        {
            Networks[Index].Activate();
        }
        else
        {
            Networks[Index].Deactivate();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Network with ID '%s' not found."), *NetworkID);
    }
}

void ASystemAdministrationNetwork::DisplayNetworks() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all networks..."));
    for (const FNetworkEntry& N : Networks)
    {
        N.Display();
    }
}

void ASystemAdministrationNetwork::ToggleInfinityMatrix(bool bActivate)
{
    bInfinityMatrixActive = bActivate;
    UE_LOG(LogTemp, Log, TEXT("Infinity Matrix power toggled. Active: %s"), bInfinityMatrixActive ? TEXT("true") : TEXT("false"));
}

void ASystemAdministrationNetwork::AutoAddNetwork()
{
    const FString Name = FString::Printf(TEXT("Network-%d"), Networks.Num() + 1);
    const FString Type = (FMath::FRand() > 0.5f) ? TEXT("Public") : TEXT("Private");
    const bool bIsActive = (FMath::FRand() > 0.5f);
    AddNetwork(Name, Type, bIsActive);
}

void ASystemAdministrationNetwork::AutoToggleNetwork()
{
    if (Networks.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, Networks.Num() - 1);
        const bool bActivate = !Networks[Index].bIsActive;
        ToggleNetwork(Networks[Index].NetworkID, bActivate);
    }
}

void ASystemAdministrationNetwork::AutoDisplayNetworks()
{
    DisplayNetworks();
}

void ASystemAdministrationNetwork::AutoToggleInfinityMatrix()
{
    ToggleInfinityMatrix(!bInfinityMatrixActive);
}

