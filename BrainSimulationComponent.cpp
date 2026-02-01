// Converted from Unity MonoBehaviour BrainSimulation to Unreal ActorComponent.
#include "BrainSimulationComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

UBrainSimulationComponent::UBrainSimulationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBrainSimulationComponent::BeginPlay()
{
    Super::BeginPlay();

    GenerateStimuli();
    EncodeStimuli();
    VisualizeStimuli();
}

void UBrainSimulationComponent::GenerateStimuli()
{
    Stimuli.SetNumZeroed(NumberOfStimuli);
    for (int32 Index = 0; Index < NumberOfStimuli; ++Index)
    {
        Stimuli[Index] = FMath::FRandRange(-StimulusRange, StimulusRange);
    }
}

void UBrainSimulationComponent::EncodeStimuli()
{
    EncodedStimuli.SetNumZeroed(NumberOfStimuli);
    const float Average = GetAverageStimulus();

    for (int32 Index = 0; Index < NumberOfStimuli; ++Index)
    {
        const float Difference = Stimuli[Index] - Average;
        EncodedStimuli[Index] = FMath::Abs(Difference) > DifferenceThreshold ? Difference : 0.0f;
    }
}

float UBrainSimulationComponent::GetAverageStimulus() const
{
    if (Stimuli.Num() == 0)
    {
        return 0.0f;
    }

    float Sum = 0.0f;
    for (float Value : Stimuli)
    {
        Sum += Value;
    }
    return Sum / Stimuli.Num();
}

void UBrainSimulationComponent::VisualizeStimuli() const
{
    FString StimuliString;
    FString EncodedString;

    for (int32 Index = 0; Index < Stimuli.Num(); ++Index)
    {
        StimuliString += FString::SanitizeFloat(Stimuli[Index]);
        EncodedString += FString::SanitizeFloat(EncodedStimuli[Index]);

        if (Index < Stimuli.Num() - 1)
        {
            StimuliString += TEXT(", ");
            EncodedString += TEXT(", ");
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Original Stimuli: %s"), *StimuliString);
    UE_LOG(LogTemp, Log, TEXT("Encoded Stimuli: %s"), *EncodedString);
}
