// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationAnalysisSystem.generated.h"

USTRUCT(BlueprintType)
struct FSystemAdminAnalysisPacket
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Analysis|Packet")
    FString PacketID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Analysis|Packet")
    FString Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Analysis|Packet")
    FString Direction; // "Input" or "Output"

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Analysis|Packet")
    bool bIsAnalyzed = false;

    FSystemAdminAnalysisPacket() {}
    FSystemAdminAnalysisPacket(const FString& InContent, const FString& InDirection)
        : PacketID(FGuid::NewGuid().ToString())
        , Content(InContent)
        , Direction(InDirection)
        , bIsAnalyzed(false)
    {}

    void MarkAnalyzed()
    {
        bIsAnalyzed = true;
        UE_LOG(LogTemp, Log, TEXT("Packet '%s' analyzed. Direction: %s, Content: %s"), *PacketID, *Direction, *Content);
    }
};

USTRUCT(BlueprintType)
struct FAdaptabilityRecord
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Analysis|Adaptability")
    FString RecordID;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Analysis|Adaptability")
    FString Content;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Analysis|Adaptability")
    FString AdjustmentDetails;

    FAdaptabilityRecord() {}
    FAdaptabilityRecord(const FString& InContent, const FString& InAdjustment)
        : RecordID(FGuid::NewGuid().ToString())
        , Content(InContent)
        , AdjustmentDetails(InAdjustment)
    {}
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationAnalysisSystem : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationAnalysisSystem();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Analysis")
    void AddDataPacket(const FString& Content, const FString& Direction);

private:
    // Channels
    TQueue<FSystemAdminAnalysisPacket> InputChannel;
    TArray<FSystemAdminAnalysisPacket> OutputChannel; // Stored for visibility similar to demo

    // Adaptability records
    TArray<FAdaptabilityRecord> AdaptabilityRecords;

    // Timers
    FTimerHandle TimerHandle_AutoInput;
    FTimerHandle TimerHandle_AutoOutput;
    FTimerHandle TimerHandle_ProcessNext;
    FTimerHandle TimerHandle_DisplayRecords;

    // Logic
    void AnalyzeDataPacket(FSystemAdminAnalysisPacket& Packet);
    void CreateAdaptabilityRecord(const FString& Content, const FString& AdjustmentDetails);
    void CatalogData(const FSystemAdminAnalysisPacket& Packet);

    void ProcessNextPacket();
    void DisplayAdaptabilityRecords();

    void AutoGenerateInputPacket();
    void AutoGenerateOutputPacket();
};

