#pragma once

#include "CoreMinimal.h"
#include "QuantumElementTwo.h" // For FComplexSimple definition
#include "QuantumElement.generated.h"

USTRUCT(BlueprintType)
struct PEKBGGAP_API FQuantumElement
{
    GENERATED_BODY()

    FQuantumElement() = default;
    FQuantumElement(const FVector& InPosition,
                    float InEnergyLevel,
                    const FComplexSimple& InProbabilityWaveFunction,
                    const FVector& InHyperDimensionalCoordXYZ,
                    float InHyperDimensionalCoordW)
        : Position(InPosition)
        , EnergyLevel(InEnergyLevel)
        , ProbabilityWaveFunction(InProbabilityWaveFunction)
        , HyperDimensionalCoordXYZ(InHyperDimensionalCoordXYZ)
        , HyperDimensionalCoordW(InHyperDimensionalCoordW)
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FVector Position = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float EnergyLevel = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FComplexSimple ProbabilityWaveFunction; // Simple complex value

    // 4D hyper coordinate represented as XYZ + W
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FVector HyperDimensionalCoordXYZ = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float HyperDimensionalCoordW = 0.f;

    // Methods analogous to Unity version
    void TransitionState(const FComplexSimple& NewWaveFunc, float TimeDelta)
    {
        const float T = FMath::Clamp(TimeDelta, 0.f, 1.f);
        ProbabilityWaveFunction = FComplexSimple::Lerp(ProbabilityWaveFunction, NewWaveFunc, T);
    }

    float CalculateProbabilityDensity() const
    {
        return ProbabilityWaveFunction.MagnitudeSquared();
    }
};
