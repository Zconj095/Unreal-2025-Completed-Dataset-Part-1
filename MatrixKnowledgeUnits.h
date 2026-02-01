#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixKnowledgeUnits.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixKnowledgeUnits : public AActor
{
    GENERATED_BODY()

public:
    AMatrixKnowledgeUnits();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Knowledge")
    void AddKnowledgeUnit(const FString& Data);

    UFUNCTION(BlueprintCallable, Category = "Matrix Knowledge")
    void ProcessKnowledgeUnits();

    UFUNCTION(BlueprintCallable, Category = "Matrix Knowledge")
    void RetrieveKnowledgeUnits() const;

    UFUNCTION(BlueprintPure, Category = "Matrix Knowledge")
    float GetTotalEnergy() const { return TotalEnergy; }

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float AddUnitInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float ProcessUnitsInterval = 7.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float RetrieveUnitsInterval = 10.f; // seconds

private:
    struct FKnowledgeUnit
    {
        FString UnitID;
        FString Data;
        bool bIsProcessed;

        explicit FKnowledgeUnit(const FString& InData)
            : UnitID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , Data(InData)
            , bIsProcessed(false)
        {
        }

        void MarkProcessed()
        {
            bIsProcessed = true;
            UE_LOG(LogTemp, Log, TEXT("Knowledge Unit '%s' has been processed."), *UnitID);
        }
    };

    float CalculateUnitEnergy(const FString& Data) const;

    TArray<FKnowledgeUnit> KnowledgeUnits;
    float TotalEnergy = 0.f;

    float AddUnitTimer = 0.f;
    float ProcessUnitsTimer = 0.f;
    float RetrieveUnitsTimer = 0.f;
};

