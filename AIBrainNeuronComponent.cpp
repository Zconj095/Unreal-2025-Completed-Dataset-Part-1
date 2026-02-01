// Converted from Unity C# to Unreal C++
#include "AIBrainNeuronComponent.h"

UAIBrainNeuronComponent::UAIBrainNeuronComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAIBrainNeuronComponent::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the list is initialized (TArray starts empty by default)
    AIBrainConnections.Reset();
}

void UAIBrainNeuronComponent::Process_Implementation()
{
    // Override in derived Blueprint/C++ classes to implement neuron behavior.
}

void UAIBrainNeuronComponent::UpdateState(float NewState)
{
    State = NewState;
    UE_LOG(LogTemp, Log, TEXT("Neuron state updated to: %f"), State);
}
