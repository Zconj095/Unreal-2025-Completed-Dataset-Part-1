// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRSBrain.generated.h"

USTRUCT(BlueprintType)
struct FNeuralCircuit
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRS|Brain|Circuit")
    FString CircuitID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRS|Brain|Circuit")
    FString Description;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRS|Brain|Circuit")
    bool bIsActive = true;

    FNeuralCircuit() {}
    explicit FNeuralCircuit(const FString& InDescription)
        : CircuitID(FGuid::NewGuid().ToString())
        , Description(InDescription)
        , bIsActive(true)
    {}

    void ToggleCircuit(bool bActivate)
    {
        bIsActive = bActivate;
        UE_LOG(LogTemp, Log, TEXT("Circuit '%s' is now %s"), *Description, bIsActive ? TEXT("Active") : TEXT("Inactive"));
    }
};

USTRUCT(BlueprintType)
struct FSensoryInput
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRS|Brain|Sensory")
    FString InputID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRS|Brain|Sensory")
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRS|Brain|Sensory")
    float Intensity = 0.f; // 0..1

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRS|Brain|Sensory")
    bool bIsProcessed = false;

    FSensoryInput() {}
    FSensoryInput(const FString& InType, float InIntensity)
        : InputID(FGuid::NewGuid().ToString())
        , Type(InType)
        , Intensity(FMath::Clamp(InIntensity, 0.f, 1.f))
        , bIsProcessed(false)
    {}

    void ProcessInput()
    {
        bIsProcessed = true;
        UE_LOG(LogTemp, Log, TEXT("Sensory Input '%s' processed with intensity %.2f"), *Type, Intensity);
    }
};

USTRUCT(BlueprintType)
struct FKnowledge
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRS|Brain|Knowledge")
    FString KnowledgeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRS|Brain|Knowledge")
    FString Description;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRS|Brain|Knowledge")
    bool bIsUsedForDecision = false;

    FKnowledge() {}
    explicit FKnowledge(const FString& InDescription)
        : KnowledgeID(FGuid::NewGuid().ToString())
        , Description(InDescription)
        , bIsUsedForDecision(false)
    {}

    void UseForDecision()
    {
        bIsUsedForDecision = true;
        UE_LOG(LogTemp, Log, TEXT("Knowledge '%s' used for decision-making."), *Description);
    }
};

UCLASS()
class PEKBGGAP_API AVRSBrain : public AActor
{
    GENERATED_BODY()

public:
    AVRSBrain();

protected:
    virtual void BeginPlay() override;

public:
    // API similar to Unity methods
    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void AddNeuralCircuit(const FString& Description);

    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void ToggleRandomCircuit();

    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void AddSensoryInput(const FString& Type, float Intensity);

    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void ProcessSensoryInputs();

    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void AddKnowledge(const FString& Description);

    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void UseRandomKnowledgeForDecision();

    UFUNCTION(BlueprintCallable, Category = "VRS|Brain")
    void DisplayBrainStatus() const;

private:
    // Data
    UPROPERTY()
    TArray<FNeuralCircuit> NeuralCircuits;

    UPROPERTY()
    TArray<FSensoryInput> SensoryInputs;

    UPROPERTY()
    TArray<FKnowledge> KnowledgePackets;

    // Timers
    FTimerHandle TimerHandle_ProcessSensory;
    FTimerHandle TimerHandle_ToggleCircuit;
    FTimerHandle TimerHandle_UseKnowledge;
    FTimerHandle TimerHandle_DisplayStatus;
};

