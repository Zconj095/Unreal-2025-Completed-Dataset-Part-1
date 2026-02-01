// Converted from Unity C# to Unreal C++
#include "VRSBrain.h"

#include "Engine/World.h"
#include "TimerManager.h"

AVRSBrain::AVRSBrain()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AVRSBrain::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("VR Species Brain Initialized."));

    // Initial setup
    AddNeuralCircuit(TEXT("Motor Function Circuit"));
    AddNeuralCircuit(TEXT("Sensory Feedback Circuit"));

    AddSensoryInput(TEXT("Vision"), 0.8f);
    AddSensoryInput(TEXT("Hearing"), 0.5f);

    AddKnowledge(TEXT("Survival Instincts"));
    AddKnowledge(TEXT("Learned Reflexes"));

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Process sensory inputs every 5s, start after 2s
        TM.SetTimer(
            TimerHandle_ProcessSensory,
            this,
            &AVRSBrain::ProcessSensoryInputs,
            5.0f,
            true,
            2.0f);

        // Toggle random circuit every 7s, start after 3s
        TM.SetTimer(
            TimerHandle_ToggleCircuit,
            this,
            &AVRSBrain::ToggleRandomCircuit,
            7.0f,
            true,
            3.0f);

        // Use random knowledge every 6s, start after 4s
        TM.SetTimer(
            TimerHandle_UseKnowledge,
            this,
            &AVRSBrain::UseRandomKnowledgeForDecision,
            6.0f,
            true,
            4.0f);

        // Display brain status every 20s, start after 10s
        TM.SetTimer(
            TimerHandle_DisplayStatus,
            this,
            &AVRSBrain::DisplayBrainStatus,
            20.0f,
            true,
            10.0f);
    }
}

void AVRSBrain::AddNeuralCircuit(const FString& Description)
{
    FNeuralCircuit Circuit(Description);
    NeuralCircuits.Add(Circuit);
    UE_LOG(LogTemp, Log, TEXT("Neural Circuit Added: %s"), *Description);
}

void AVRSBrain::ToggleRandomCircuit()
{
    if (NeuralCircuits.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, NeuralCircuits.Num() - 1);
        const bool bActivate = !NeuralCircuits[Index].bIsActive;
        NeuralCircuits[Index].ToggleCircuit(bActivate);
    }
}

void AVRSBrain::AddSensoryInput(const FString& Type, float Intensity)
{
    FSensoryInput Input(Type, Intensity);
    SensoryInputs.Add(Input);
    UE_LOG(LogTemp, Log, TEXT("Sensory Input Added: %s with intensity %.2f"), *Type, Intensity);
}

void AVRSBrain::ProcessSensoryInputs()
{
    UE_LOG(LogTemp, Log, TEXT("Processing all sensory inputs..."));
    for (FSensoryInput& Input : SensoryInputs)
    {
        if (!Input.bIsProcessed)
        {
            Input.ProcessInput();
        }
    }
}

void AVRSBrain::AddKnowledge(const FString& Description)
{
    FKnowledge K(Description);
    KnowledgePackets.Add(K);
    UE_LOG(LogTemp, Log, TEXT("Knowledge Added: %s"), *Description);
}

void AVRSBrain::UseRandomKnowledgeForDecision()
{
    if (KnowledgePackets.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, KnowledgePackets.Num() - 1);
        KnowledgePackets[Index].UseForDecision();
    }
}

void AVRSBrain::DisplayBrainStatus() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying VR Species Brain Status:"));

    UE_LOG(LogTemp, Log, TEXT("Neural Circuits:"));
    for (const FNeuralCircuit& C : NeuralCircuits)
    {
        UE_LOG(LogTemp, Log, TEXT(" - Circuit: %s, Active: %s"), *C.Description, C.bIsActive ? TEXT("true") : TEXT("false"));
    }

    UE_LOG(LogTemp, Log, TEXT("Sensory Inputs:"));
    for (const FSensoryInput& S : SensoryInputs)
    {
        UE_LOG(LogTemp, Log, TEXT(" - Input: %s, Intensity: %.2f, Processed: %s"), *S.Type, S.Intensity, S.bIsProcessed ? TEXT("true") : TEXT("false"));
    }

    UE_LOG(LogTemp, Log, TEXT("Knowledge Packets:"));
    for (const FKnowledge& K : KnowledgePackets)
    {
        UE_LOG(LogTemp, Log, TEXT(" - Knowledge: %s, Used for Decision: %s"), *K.Description, K.bIsUsedForDecision ? TEXT("true") : TEXT("false"));
    }
}

