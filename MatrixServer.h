#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixServer.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixServer : public AActor
{
    GENERATED_BODY()

public:
    AMatrixServer();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Server")
    void AddOperatingSystem();

    UFUNCTION(BlueprintCallable, Category = "Matrix Server")
    void AddWordToOS(int32 OSIndex, const FString& WordText);

    UFUNCTION(BlueprintCallable, Category = "Matrix Server")
    void PickWordFromOS(int32 OSIndex);

    UFUNCTION(BlueprintCallable, Category = "Matrix Server")
    void RetrieveOSStatus() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float AddOSInterval = 10.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float AddWordInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float RetrieveStatusInterval = 15.f; // seconds

private:
    struct FWord
    {
        FString Text;

        explicit FWord(const FString& InText) : Text(InText) {}
        FWord() = default;
    };

    struct FOperatingSystem
    {
        FString OSID;
        TArray<FWord> Words;

        FOperatingSystem()
            : OSID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
        {
        }

        void AddWord(const FString& WordText)
        {
            Words.Emplace(WordText);
            UE_LOG(LogTemp, Log, TEXT("Word '%s' added to OS '%s'."), *WordText, *OSID);
        }

        const FWord* PickWord() const
        {
            if (Words.Num() > 0)
            {
                const int32 Index = FMath::RandRange(0, Words.Num() - 1);
                UE_LOG(LogTemp, Log, TEXT("Word picked from OS '%s': %s"), *OSID, *Words[Index].Text);
                return &Words[Index];
            }

            UE_LOG(LogTemp, Warning, TEXT("OS '%s' has no words to pick from."), *OSID);
            return nullptr;
        }
    };

    // Data
    TArray<FOperatingSystem> OperatingSystems;

    // Timers
    float AddOSTimer = 0.f;
    float AddWordTimer = 0.f;
    float RetrieveStatusTimer = 0.f;
};

