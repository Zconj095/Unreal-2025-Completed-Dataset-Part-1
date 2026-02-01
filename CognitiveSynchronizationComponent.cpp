// Converted from Unity MonoBehaviour CognitiveSynchronization to Unreal ActorComponent.
#include "CognitiveSynchronizationComponent.h"
#include "GameFramework/Actor.h"

#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

UCognitiveSynchronizationComponent::UCognitiveSynchronizationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCognitiveSynchronizationComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeNeurons();
    InitializeConnections();

    if (AActor* Owner = GetOwner())
    {
        GetWorld()->GetTimerManager().SetTimer(
            PhaseUpdateHandle,
            this,
            &UCognitiveSynchronizationComponent::UpdateNeuronStates,
            PhaseUpdateInterval,
            true);
    }
}

void UCognitiveSynchronizationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(PhaseUpdateHandle);
    }

    Super::EndPlay(EndPlayReason);
}

void UCognitiveSynchronizationComponent::InitializeNeurons()
{
    Neurons.SetNumZeroed(NumberOfNeurons);
    for (int32 Index = 0; Index < NumberOfNeurons; ++Index)
    {
        Neurons[Index].Phase = FMath::FRandRange(0.0f, 2.0f * PI);
        Neurons[Index].FiringRate = FMath::FRandRange(0.1f, 1.0f);
    }
    UE_LOG(LogTemp, Log, TEXT("Initialized %d neurons."), NumberOfNeurons);
}

void UCognitiveSynchronizationComponent::InitializeConnections()
{
    ConnectionWeights.SetNumZeroed(NumberOfNeurons * NumberOfNeurons);
    for (int32 Row = 0; Row < NumberOfNeurons; ++Row)
    {
        for (int32 Col = 0; Col < NumberOfNeurons; ++Col)
        {
            const int32 Index = GetWeightIndex(Row, Col);
            ConnectionWeights[Index] = (Row != Col)
                ? FMath::FRandRange(0.1f, 1.0f)
                : 0.0f;
        }
    }
    UE_LOG(LogTemp, Log, TEXT("Connections initialized."));
}

void UCognitiveSynchronizationComponent::UpdateNeuronStates()
{
    TArray<float> NewPhases;
    NewPhases.SetNumZeroed(NumberOfNeurons);

    for (int32 I = 0; I < NumberOfNeurons; ++I)
    {
        float PhaseSum = 0.0f;
        for (int32 J = 0; J < NumberOfNeurons; ++J)
        {
            if (I == J)
            {
                continue;
            }
            const float PhaseDifference = Neurons[J].Phase - Neurons[I].Phase;
            const float Weight = ConnectionWeights[GetWeightIndex(I, J)];
            PhaseSum += Weight * FMath::Sin(PhaseDifference);
        }
        NewPhases[I] = Neurons[I].Phase + CouplingStrength * PhaseSum;
    }

    for (int32 Index = 0; Index < NumberOfNeurons; ++Index)
    {
        Neurons[Index].Phase = NormalizePhase(NewPhases[Index]);
    }

    DebugNeuronStates();
}

void UCognitiveSynchronizationComponent::DebugNeuronStates() const
{
    for (int32 Index = 0; Index < NumberOfNeurons; ++Index)
    {
        UE_LOG(
            LogTemp,
            Log,
            TEXT("Neuron %d: Phase = %.2f, Firing Rate = %.2f"),
            Index,
            Neurons[Index].Phase,
            Neurons[Index].FiringRate);
    }
}

float UCognitiveSynchronizationComponent::NormalizePhase(float Phase) const
{
    const float TwoPi = 2.0f * PI;
    return FMath::Fmod(Phase + TwoPi, TwoPi);
}

int32 UCognitiveSynchronizationComponent::GetWeightIndex(int32 Row, int32 Col) const
{
    return Row * NumberOfNeurons + Col;
}
