#include "StructuralComplexityIndexComponent.h"

#include "Math/UnrealMathUtility.h"

UStructuralComplexityIndexComponent::UStructuralComplexityIndexComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralComplexityIndexComponent::BeginPlay()
{
    Super::BeginPlay();
    const float SCIValue = CalculateSCI();
    UE_LOG(LogTemp, Log, TEXT("Structural Complexity Index (SCI): %.4f"), SCIValue);
}

float UStructuralComplexityIndexComponent::CalculateSCI() const
{
    if (SpecializedBrainRegions <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Specialized Brain Regions (S) must be greater than 0."));
        return 0.0f;
    }

    const float NeuronTerm = Alpha * FMath::Pow(static_cast<float>(NumberOfNeurons), 2);
    const float ConnectivityTerm = Beta * NeuralConnectivity * FMath::Log2(static_cast<float>(SpecializedBrainRegions));
    return NeuronTerm + ConnectivityTerm;
}
