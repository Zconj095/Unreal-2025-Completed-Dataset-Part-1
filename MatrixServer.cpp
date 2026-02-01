#include "MatrixServer.h"

#include "Misc/Guid.h"

AMatrixServer::AMatrixServer()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixServer::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Server Initialized."));
}

void AMatrixServer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timers
    AddOSTimer += DeltaSeconds;
    AddWordTimer += DeltaSeconds;
    RetrieveStatusTimer += DeltaSeconds;

    // Automate adding operating systems
    if (AddOSTimer >= AddOSInterval)
    {
        AddOperatingSystem();
        AddOSTimer = 0.f;
    }

    // Automate adding words to the first OS
    if (AddWordTimer >= AddWordInterval && OperatingSystems.Num() > 0)
    {
        const int32 Rand = FMath::RandRange(1, 100);
        AddWordToOS(0, FString::Printf(TEXT("Word_%d"), Rand));
        AddWordTimer = 0.f;
    }

    // Automate retrieving OS status
    if (RetrieveStatusTimer >= RetrieveStatusInterval)
    {
        RetrieveOSStatus();
        RetrieveStatusTimer = 0.f;
    }
}

void AMatrixServer::AddOperatingSystem()
{
    if (OperatingSystems.Num() >= 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("Maximum of 3 operating systems can be connected to the server."));
        return;
    }

    FOperatingSystem OS;
    UE_LOG(LogTemp, Log, TEXT("Operating System added to the server - OSID: %s"), *OS.OSID);
    OperatingSystems.Add(MoveTemp(OS));
}

void AMatrixServer::AddWordToOS(int32 OSIndex, const FString& WordText)
{
    if (OperatingSystems.IsValidIndex(OSIndex))
    {
        OperatingSystems[OSIndex].AddWord(WordText);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Operating system index '%d' is out of range."), OSIndex);
    }
}

void AMatrixServer::PickWordFromOS(int32 OSIndex)
{
    if (OperatingSystems.IsValidIndex(OSIndex))
    {
        OperatingSystems[OSIndex].PickWord();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Operating system index '%d' is out of range."), OSIndex);
    }
}

void AMatrixServer::RetrieveOSStatus() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving operating system status..."));
    for (int32 i = 0; i < OperatingSystems.Num(); ++i)
    {
        const FOperatingSystem& OS = OperatingSystems[i];
        UE_LOG(LogTemp, Log, TEXT("OS %d - ID: %s, Words Count: %d"), i + 1, *OS.OSID, OS.Words.Num());
    }
}

