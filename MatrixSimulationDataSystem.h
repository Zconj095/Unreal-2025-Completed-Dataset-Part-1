#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSimulationDataSystem.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSimulationDataSystem : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSimulationDataSystem();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Data System")
    void TransferData(const FString& Source, const FString& Destination, const FString& Content);

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Data System")
    void DisplayReservoirData() const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Simulation Data System")
    void ClearReservoir();

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float OperationInterval = 5.f; // seconds

private:
    struct FDataPacket
    {
        FString PacketID;
        FString SourceSystem;
        FString DestinationSystem;
        FString Content;

        FDataPacket() = default;
        FDataPacket(const FString& InSource, const FString& InDestination, const FString& InContent)
            : PacketID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , SourceSystem(InSource)
            , DestinationSystem(InDestination)
            , Content(InContent)
        {
        }
    };

    class FDataAnalysisChamber
    {
    public:
        void StoreData(const FDataPacket& Packet)
        {
            Reservoir.Add(Packet);
            UE_LOG(LogTemp, Log, TEXT("Data Packet Stored in Reservoir - ID: %s, Content: %s"), *Packet.PacketID, *Packet.Content);
        }

        const FDataPacket* RetrieveDataByID(const FString& PacketID) const
        {
            const FDataPacket* Found = nullptr;
            for (const FDataPacket& P : Reservoir)
            {
                if (P.PacketID == PacketID)
                {
                    Found = &P;
                    break;
                }
            }

            if (Found)
            {
                UE_LOG(LogTemp, Log, TEXT("Data Packet Retrieved from Reservoir - ID: %s, Content: %s"), *Found->PacketID, *Found->Content);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Data Packet with ID '%s' not found in reservoir."), *PacketID);
            }
            return Found;
        }

        void ClearReservoir()
        {
            Reservoir.Reset();
            UE_LOG(LogTemp, Log, TEXT("Reservoir cleared."));
        }

        void DisplayAllData() const
        {
            UE_LOG(LogTemp, Log, TEXT("Displaying all data in the reservoir..."));
            for (const FDataPacket& P : Reservoir)
            {
                UE_LOG(LogTemp, Log, TEXT("Packet - ID: %s, Source: %s, Destination: %s, Content: %s"), *P.PacketID, *P.SourceSystem, *P.DestinationSystem, *P.Content);
            }
        }

        int32 GetCount() const { return Reservoir.Num(); }

        bool GetPacketIDAtIndex(int32 Index, FString& OutPacketID) const
        {
            if (Reservoir.IsValidIndex(Index))
            {
                OutPacketID = Reservoir[Index].PacketID;
                return true;
            }
            return false;
        }

    private:
        TArray<FDataPacket> Reservoir;
    };

    void SendToAnalysisChamber(const FDataPacket& Packet);
    void RetrieveRandomPacket();
    void PerformAutomatedOperations();

    // Chamber instance
    FDataAnalysisChamber DataChamber;

    // Timer
    float OperationTimer = 0.f;
};

