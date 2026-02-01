#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixSerialCode.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixSerialCode : public AActor
{
    GENERATED_BODY()

public:
    AMatrixSerialCode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Serial Code")
    void AddWordWithSerialCode(const FString& Word, const FString& SerialCode);

    // Returns the SerialCode for a word; empty string if not found
    UFUNCTION(BlueprintCallable, Category = "Matrix Serial Code")
    FString SearchWord(const FString& Word) const;

    // Returns the Word for a serial code; empty string if not found
    UFUNCTION(BlueprintCallable, Category = "Matrix Serial Code")
    FString SearchSerialCode(const FString& SerialCode) const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Serial Code")
    void RetrieveAllEntries() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float AddEntryInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float SearchWordInterval = 7.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float SearchCodeInterval = 10.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float RetrieveEntriesInterval = 15.f; // seconds

private:
    struct FSerialCodeEntry
    {
        FString Word;
        FString SerialCode;

        FSerialCodeEntry() = default;
        FSerialCodeEntry(const FString& InWord, const FString& InSerial)
            : Word(InWord), SerialCode(InSerial) {}
    };

    // Lowercase word -> entry
    TMap<FString, FSerialCodeEntry> SerialCodeDatabase;

    // Timers
    float AddEntryTimer = 0.f;
    float SearchWordTimer = 0.f;
    float SearchCodeTimer = 0.f;
    float RetrieveEntriesTimer = 0.f;
};

