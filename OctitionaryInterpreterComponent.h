// Octitionary Interpreter: maps user-defined symbols to codes, expands formulas, evaluates, and exports binary
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OctitionaryInterpreterComponent.generated.h"

USTRUCT(BlueprintType)
struct PEKBGGAP_API FOctitionaryPair
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Key;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Value;
};

USTRUCT(BlueprintType)
struct PEKBGGAP_API FOctitionaryEvaluation
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly)
    FString Expanded;
    UPROPERTY(BlueprintReadOnly)
    bool bHasNumericValue = false;
    UPROPERTY(BlueprintReadOnly)
    double NumericValue = 0.0;
    UPROPERTY(BlueprintReadOnly)
    FString BinaryBits;
    // uint64 is not Blueprint-supported; expose hex string for Blueprints and keep raw value as native-only
    UPROPERTY(BlueprintReadOnly)
    FString HashHex;

    uint64 Hash64 = 0ULL;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UOctitionaryInterpreterComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UOctitionaryInterpreterComponent();

    // Mappings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Octitionary")
    TArray<FOctitionaryPair> LetterPairs; // letters/syllables -> codes

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Octitionary")
    TArray<FOctitionaryPair> SymbolPairs; // special symbols: ∞, □, etc.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Octitionary")
    TArray<FOctitionaryPair> DigitSemantics; // 0..9 -> labels (documentation)

    UFUNCTION(BlueprintCallable, Category="Octitionary")
    void ClearAll();

    UFUNCTION(BlueprintCallable, Category="Octitionary")
    void AddPairs(const TArray<FOctitionaryPair>& Pairs, bool bLetters = true);

    UFUNCTION(BlueprintCallable, Category="Octitionary")
    FOctitionaryEvaluation Evaluate(const FString& Formula);

    UFUNCTION(BlueprintCallable, Category="Octitionary|Presets")
    void LoadPreset_SongOfTemporalCollaboration();

private:
    FString ExpandFormula(const FString& In) const;
    bool TryEvalArithmetic(const FString& In, double& Out) const;
    static FString ToBinaryBits(const FString& In);
    static uint64 HashFNV1a64(const FString& In);
};
