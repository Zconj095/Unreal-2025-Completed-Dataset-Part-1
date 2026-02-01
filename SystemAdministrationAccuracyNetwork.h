// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationAccuracyNetwork.generated.h"

USTRUCT(BlueprintType)
struct FSystemAdminDataPacket
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Packet")
    FString PacketID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Packet")
    FString Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Packet")
    FString Source;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Packet")
    FString Destination;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Packet")
    bool bIsAuthorized = false;

    FSystemAdminDataPacket() {}

    FSystemAdminDataPacket(const FString& InContent, const FString& InSource, const FString& InDestination, bool bInAuthorized)
        : PacketID(FGuid::NewGuid().ToString())
        , Content(InContent)
        , Source(InSource)
        , Destination(InDestination)
        , bIsAuthorized(bInAuthorized)
    {
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationAccuracyNetwork : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationAccuracyNetwork();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Packets")
    void AddDataPacket(const FString& Content, const FString& Source, const FString& Destination, bool bIsAuthorized);

private:
    // Channels
    TQueue<FSystemAdminDataPacket> InputChannel;
    TArray<FSystemAdminDataPacket> OutputChannel;

    // Timers (InvokeRepeating equivalents)
    FTimerHandle TimerHandle_AutoGenerate;
    FTimerHandle TimerHandle_ProcessNext;
    FTimerHandle TimerHandle_DisplayOutput;

    // Logic
    void ProcessDataPacket(FSystemAdminDataPacket& Packet);
    FString CalculateSafeRoute(const FString& Source, const FString& Destination) const;
    void TransferToHeadAdmin(FSystemAdminDataPacket& Packet);
    void CatalogData(FSystemAdminDataPacket& Packet);
    void EncodeData(const FSystemAdminDataPacket& Packet);

    void ProcessNextPacket();
    void DisplayOutputChannel();
    void AutoGeneratePackets();
};

